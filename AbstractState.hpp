#ifndef ABSTRACTSTATE_HPP_
#define ABSTRACTSTATE_HPP_

//-----[ TEMPLATE CLASS: AbstractState ]----------------------------------------
template <typename CTX>
class AbstractState :
	public CTX::visitor_type
{
	template <typename CTX_, typename T_, typename PARENT_, typename ... CHILDREN_>
	friend
	class State;
	
	template <typename CTX_, typename ROOT_>
	friend
	class StateMachine;
	
	using ctx_type = CTX;
	using visitor_type = typename ctx_type::visitor_type;
	
public:
	AbstractState(ctx_type& context):
		_context(context)
	{
		
	}
	
	virtual ~AbstractState() = default;
	
public:
	virtual state_return_type dispatch(const AbstractEvent<visitor_type>& e) {
		return e.accept(*this);
	}
	
	virtual ctti::detail::cstring name() const = 0;
	virtual ctti::detail::cstring childName() const = 0;
		
protected:
	inline ctx_type& context() const { return _context; }
	
	void defer(const AbstractEvent<visitor_type>& e) {
		_context.defer(e);
	}
		
private:
	virtual void _init() {}
	virtual void _deinit() {}
	
private:
	ctx_type& _context;
};

#endif //ABSTRACTSTATE_HPP_