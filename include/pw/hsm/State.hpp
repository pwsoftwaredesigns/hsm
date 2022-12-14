#ifndef PW_HSM_STATE_HPP_
#define PW_HSM_STATE_HPP_

#include "_common.hpp"
#include "AbstractState.hpp"
#include "first_of.hpp"
#include <ctti/nameof.hpp>
#include <functional>
#include <memory>
#if PW_HSM_USE_ETL == 1
	#include <etl/variant_pool.h>
#endif

namespace pw::hsm {

template <typename T, typename U, typename ENABLE = void>
struct nearest_ancestor {
	using type = typename nearest_ancestor<T, typename U::parent_type>::type;
};

template <typename T, typename U>
struct nearest_ancestor<T, U, std::enable_if_t<std::is_same_v<T, typename U::parent_type>>> {
	using type = U;
};

//-----[ TEMPLATE CLASS: State ]------------------------------------------------
/**
* @tparam CHILDREN A list of state types which are immediate children of this
*         state (i.e., which have this state as parent).  The first type in this
*         list will be considered the initial state.
*
*
*
* Example:
*
* class Root;
* class State1 : public State<MyState, Root, State11, State12>;
*/
template <typename T, typename VISITOR, typename PARENT, typename ... CHILDREN>
class State : 
	public AbstractState<VISITOR/*typename PARENT::visitor_type*/>
{
	template <typename T_, typename VISITOR_, typename PARENT_, typename ... CHILDREN_>
	friend
	class State;
	
public:
	using parent_type = PARENT;
	//using visitor_type = typename parent_type::visitor_type;
	using visitor_type = VISITOR;
	using abstract_event_type = AbstractEvent<visitor_type>;
		
private:
#if PW_HSM_USE_ETL == 1
	using unique_ptr_type = std::unique_ptr<AbstractState<visitor_type>, std::function<void(AbstractState<visitor_type>*)>>;
#else
	using unique_ptr_type = std::unique_ptr<AbstractState<visitor_type>>;
#endif
	
	template <typename ROOT_, typename CHILD_>
	inline static constexpr bool _has_child() {
		return ROOT_::template has_child<CHILD_>();
	}
	
	template <typename CHILD_>
	inline static constexpr bool has_child() {
		//Does this state contain CHILD_?
		if constexpr ((std::is_same_v<CHILD_, CHILDREN> || ...)) {
			return true;
		} else {
			//Do any of this state's children contain CHILD?
			return (_has_child<CHILDREN, CHILD_>() || ...);
		}
	}
	
public:
	State(parent_type& parent):	
		_parent(parent)
	{
		
	}
	
	~State() {
		_deinit();
	}
	
	/**
	* @brief Dispatch an event to this state
	*
	* When dispatching an event to which has children, the event will first be
	* disaptched to the active child state.  If the child state "passes" the
	* event (i.e., returns PASS), then the event will be dispatched to this
	* state via the visitor design pattern.
	*/
	return_type dispatch(const abstract_event_type& e) {
		//Dispatch to current child first
		if (_state) {
			bool result = _state->dispatch(e)();
			if (result) return [](){ return true; };
		}
		
		return AbstractState<visitor_type>::dispatch(e);
	}
	
	/**
	* @brief Perform a transition to another state
	*
	* Transitions can only be performed by the least-comon ancestor state (i.e.,
	* the parent that contaisn both the source and destination state).  Since
	* transitioning a state involves deleting/deconstructing the associated
	* memory, the state itself cannot do this as it would delete itself.  This
	* method checks, at compile-time, if the destination state is one of its
	* children, if not, then it defers the transition to its parent.
	*
	* This is achieved by returning callback functions.
	*/
	template <typename DEST_>
	return_type transition() {
		if constexpr (has_child<DEST_>()) {
			//This state (the least-common-ancestor) will perform the transition
			return [this](){ 
				PW_HSM_TRANSITION_TRACE(childName(), ctti::nameof<DEST_>());
				this->_doTransition<DEST_>(); 
				return true; 
			};
		} else {
			//Let my parent perform the transition
			return [this](){ return this->_parent.template transition<DEST_>()(); };
		}
	}
	
	/**
	* @brief Use CTTI to get the name of this state (i.e., class)
	*/
	name_string_type name() const override { return ctti::nameof<T>(); }
		
	/**
	* @brief Use CTTI to recursively get the name of this state's deepest child
	*
	* This method will always return the name fo the deepest leaf state
	*/
	name_string_type childName() const override { 
		if (_state) return _state->childName();
		else return name();
	}
	
protected:
	/**
	* @brief Get a reference to one of this state's ancestors
	*
	* By default, this method returns this states immediate parent.  However,
	* a template of the parent type may be provided to return an ancestor
	* higher in the tree.  These inline methods should collapse at compile-
	* time.
	*/
	template <typename P_ = parent_type>
	inline auto& parent() const {
		if constexpr (std::is_same_v<P_, parent_type>) {
			return _parent;
		} else {
			return _parent.template parent<P_>();
		}
	}
	
	/**
	* @brief A helper method which returns a reference the base state machine
	*        itself (i.e., an instance of StateMachine<>)
	*/
	inline auto& ctx() const {
		return _parent.ctx();
	}
	
private:
	/**
	* @brief Create/"enter" the initial (first) child state
	*/
	void _init() override {
#if PW_HSM_USE_ETL == 1
		auto s = _statePool.template create<first_of_t<CHILDREN...>>(static_cast<T&>(*this));
#else
		auto s = std::make_unique<first_of_t<CHILDREN...>>(static_cast<T&>(*this));
#endif
		s->_init();
		
#if PW_HSM_USE_ETL == 1
		_state = unique_ptr_type{s, [this](AbstractState<visitor_type>* ptr){ _statePool.destroy(ptr); }};
#else
		_state = std::move(s);
#endif
	}
	
	/**
	* @brief Destroy/"exit" the child state
	*/
	void _deinit() override {
		if (_state) _state->_deinit();
		_state.reset();
	}
		
	/**
	* @brief Perform a transition from this state to a destination state
	*/
	template <typename DEST_> 
	void _doTransition() {
		if constexpr (std::is_same_v<T, DEST_>) {
			this->_init();
		} else {
			_deinit();
#if PW_HSM_USE_ETL == 1
			auto s = _statePool.template create<typename nearest_ancestor<T, DEST_>::type>(static_cast<T&>(*this));
#else
			auto s = std::make_unique<typename nearest_ancestor<T, DEST_>::type>(static_cast<T&>(*this));
#endif
			s->template _doTransition<DEST_>();
#if PW_HSM_USE_ETL == 1
			_state = unique_ptr_type{s, [this](AbstractState<visitor_type>* ptr){ _statePool.destroy(ptr); }};
#else
			_state = std::move(s);
#endif
		}
	}
	
private:
	parent_type& _parent;
#if PW_HSM_USE_ETL == 1
	etl::variant_pool<1, CHILDREN...> _statePool;
#endif
	unique_ptr_type _state;
};

//-----[ TEMPLATE CLASS: State ]------------------------------------------------
/**
* @brief Specialization of State with no children (i.e., a leaf state)
*/
template <typename T, typename VISITOR, typename PARENT>
class State<T, VISITOR, PARENT> : 
	public AbstractState<VISITOR/*typename PARENT::visitor_type*/>
{
	template <typename T_, typename VISITOR_, typename PARENT_, typename ... CHILDREN_>
	friend
	class State;
	
public:
	using parent_type = PARENT;
	//using visitor_type = typename parent_type::visitor_type;
	using visitor_type = VISITOR;
		
	template <typename CHILD_>
	inline static constexpr bool has_child() { return false; }
	
public:
	State(parent_type& parent) :
		_parent(parent)
	{
		
	}
	
	~State() = default;
	
public:
	template <typename DEST>
	return_type transition() {
		//This state has no children, so the parent+ state needs to transition
		return [this](){ return _parent.template transition<DEST>()(); };
	}
	
	name_string_type name() const override { return ctti::nameof<T>(); }
	name_string_type childName() const override { return name(); }
	
protected:
	template <typename P_ = parent_type>
	inline auto& parent() const {
		if constexpr (std::is_same_v<P_, parent_type>) {
			return _parent;
		} else {
			return _parent.template parent<P_>();
		}
	}
	
	inline auto& ctx() const {
		return _parent.ctx();
	}
	
private:
	template <typename DEST_> 
	void _doTransition() { 
		static_assert(std::is_same_v<T, DEST_>);
		this->_init();
	}
	
private:
	parent_type& _parent;
};

} //namespace pw::hsm

#endif //PW_HSM_STATE_HPP_
