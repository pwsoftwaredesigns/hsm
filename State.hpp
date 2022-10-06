#ifndef STATE_HPP_
#define STATE_HPP_

#include "_common.hpp"
#include "AbstractState.hpp"
#include "first_of.hpp"

//-----[ TEMPLATE CLASS: State ]------------------------------------------------
template <typename CTX, typename T, typename PARENT, typename ... CHILDREN>
class State : 
	public AbstractState<CTX>
{
	template <typename CTX_, typename T_, typename PARENT_, typename ... CHILDREN_>
	friend
	class State;
	
public:
	using ctx_type = CTX;
	using visitor_type = typename ctx_type::visitor_type;
	using parent_type = PARENT;
	using abstract_event_type = AbstractEvent<visitor_type>;
	
public:
	State(ctx_type& context, parent_type& parent):
		AbstractState<CTX>(context),
		
		_parent(parent)
	{
		
	}
	
	~State() {
		_deinit();
	}
	
	state_return_type dispatch(const abstract_event_type& e) {
		//Dispatch to current child first
		if (_state) {
			bool result = _state->dispatch(e)();
			if (result) return HANDLED;
		}
		
		return AbstractState<CTX>::dispatch(e);
	}
	
	template <typename DEST>
	state_return_type transition() {
		if constexpr ((std::is_same_v<DEST, CHILDREN> || ...)) {
			//This state (the least-common-ancestor) will perform the transition
			return [this](){ return this->_doTransition<DEST>(); };
		} else {
			//Let my parent perform the transition
			return [this](){ return this->_parent.template transition<DEST>()(); };
		}
	}
	
	ctti::detail::cstring name() const override { return ctti::nameof<T>(); }
	ctti::detail::cstring childName() const override { 
		if (_state) return _state->childName();
		else return name();
	}
	
protected:
	template <typename P_ = parent_type>
	inline auto& parent() const {
		if constexpr (std::is_same_v<P_, parent_type>) {
			return _parent;
		} else {
			return _parent.template parent<P_>();
		}
	}
	
private:
	void _init() override {
		_state = std::make_unique<first_of_t<CHILDREN...>>(this->context(), static_cast<T&>(*this));
		_state->_init();
	}
	
	void _deinit() override {
		if (_state) _state->_deinit();
		_state.reset();
	}
	
	template <typename DEST> 
	bool _doTransition() {
		std::cout << childName() << " -> " << ctti::nameof<DEST>() << std::endl;
		
		_deinit();
		_state = std::make_unique<DEST>(this->context(), static_cast<T&>(*this));
			
		return true;
	}
	
private:
	parent_type& _parent;
	std::unique_ptr<AbstractState<CTX>> _state;
};

//-----[ TEMPLATE CLASS: State ]------------------------------------------------
/**
* @brief Specialization of State with no children (i.e., a leaf state)
*/
template <typename CTX, typename T, typename PARENT>
class State<CTX, T, PARENT> : 
	public AbstractState<CTX>
{
public:
	using ctx_type = CTX;
	using visitor_type = typename ctx_type::visitor_type;
	using parent_type = PARENT;
	
public:
	State(ctx_type& context, parent_type& parent) :
		AbstractState<CTX>(context),
		
		_parent(parent)
	{
		
	}
	
	~State() = default;
	
public:
	template <typename DEST>
	state_return_type transition() {
		//This state has no children, so the parent+ state needs to transition
		return [this](){ return _parent.template transition<DEST>()(); };
	}
	
	ctti::detail::cstring name() const override { return ctti::nameof<T>(); }
	ctti::detail::cstring childName() const override { return name(); }
	
protected:
	template <typename P_ = parent_type>
	inline auto& parent() const {
		if constexpr (std::is_same_v<P_, parent_type>) {
			return _parent;
		} else {
			return _parent.template parent<P_>();
		}
	}
	
private:
	parent_type& _parent;
};

#endif //STATE_HPP_