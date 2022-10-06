#include <tuple>
#include <iostream>
#include <memory>
#include <functional>
#include <ctti/nameof.hpp>
#include <string_view>
#include <map.h>
#include <cassert>
#include "AbstractEvent.hpp"
#include "Event.hpp"
#include "AbstractState.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include "first_of.hpp"
#include "map_p.h"

#define PRINT_STATEMENT(s_) std::cout << "\033[1;32m" << #s_ << "\033[m" << std::endl; s_

#define _EXPAND(x_) _EXPANDX x_
#define _EXPANDX(...) __VA_ARGS__

#define STATE_MACHINE(name_, context_, root_, ...)\
	class name_##_VISITOR;\
	MAP_P(_STATE_MACHINE_EVENT, name_##_VISITOR, ##__VA_ARGS__)\
	_STATE_MACHINE_VISITOR(name_##_VISITOR, ##__VA_ARGS__);\
	using name_ = StateMachine<context_, root_>;
	
#define _STATE_MACHINE_EVENT(visitor_, x_) _STATE_MACHINE_EVENTX(visitor_, _EXPAND(x_))
#define _STATE_MACHINE_EVENTX(visitor_, name_, ...) _STATE_MACHINE_EVENTY(visitor_, name_, ##__VA_ARGS__)
#define _STATE_MACHINE_EVENTY(visitor_, name_, ...)\
	using name_ = Event<visitor_, ##__VA_ARGS__>;

#define _STATE_MACHINE_VISITOR(name_, ...)\
	class name_ {\
	public:\
		MAP(_STATE_MACHINE_VISITOR_VISIT, ##__VA_ARGS__)\
	}
#define _STATE_MACHINE_VISITOR_VISIT(x_) _STATE_MACHINE_VISITOR_VISITX x_
#define _STATE_MACHINE_VISITOR_VISITX(name_, ...)\
	virtual state_return_type visit(const name_& e) { return PASS; }
	
//******************************************************************************
//******************************************************************************

constexpr int A = 10;
constexpr int B = 20;

//******************************************************************************
//******************************************************************************

class EventVisitor;

struct Event1_name { static const char* value() { return "Event1"; } };
using Event1 = Event<Event1_name, EventVisitor, int>;

struct Event2_name { static const char* value() { return "Event2"; } };
using Event2 = Event<Event2_name, EventVisitor>;

//-----[ CLASS: EventVisitor ]--------------------------------------------------
class EventVisitor {
public:
	virtual state_return_type visit(const Event1& e) { return PASS; }
	virtual state_return_type visit(const Event2& e) { return PASS; }
};

class Root;
class State1;
class State11;
class State12;
class State2;
class MyStateMachine;

template<>
struct state_machine_traits<MyStateMachine> {
	using visitor_type = EventVisitor;
};

class MyStateMachine :
	public StateMachine<MyStateMachine, Root>
{
public:
	MyStateMachine():
		a(A),
		b(B)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
public:
	int a;
	int b;
};

//-----[ CLASS: Root ]----------------------------------------------------------
class Root :
	public State<Root, MyStateMachine, State1, State2>
{
public:
	Root(parent_type& parent) :
		State(parent)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
			
		//The following lines shall result in a compilation error
		//deinit();
		//init();
		
		assert(root().a == A);
		assert(root().b == B);
	}
	
	~Root() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
public:
	state_return_type visit(const Event1& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		return HANDLED;
	}
	
	state_return_type visit(const Event2& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		return HANDLED;
	}
	
public:
	int foo;
};

//-----[ CLASS: State1 ]--------------------------------------------------------
class State1 :
	public State<State1, Root, State11, State12>
{
public:
	State1(parent_type& parent) :
		State(parent)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	~State1() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	state_return_type visit(const Event1& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		return PASS;
	}
	
	state_return_type visit(const Event2& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		return PASS;
	}
	
public:
	int publicVariable;
	
private:
	int _privateVariable;
};

//-----[ CLASS: State11 ]-------------------------------------------------------
class State11 :
	public State<State11, State1>
{
public:
	State11(parent_type& parent) : 
		State(parent) 
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	~State11() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
public:
	state_return_type visit(const Event1& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		parent().publicVariable = e.arg();
		return PASS;
	}
	
	state_return_type visit(const Event2& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		//Transition to sibling state
		return transition<State12>();
	}
};

//-----[ CLASS: State12 ]-------------------------------------------------------
class State12 :
	public State<State12, State1>
{
public:
	State12(parent_type& parent) : 
		State(parent) 
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
			
		++root().a;
		++root().b;
	}
	
	~State12() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
public:
	state_return_type visit(const Event1& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		
		parent<Root>().foo = e.arg();
			
		return PASS;
	}
	
	state_return_type visit(const Event2& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		return transition<State2>();
	}
};

//-----[ CLASS: State2 ]--------------------------------------------------------
class State2 :
	public State<State2, Root>
{
public:
	State2(parent_type& parent) :
		State(parent)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	~State2() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	state_return_type visit(const Event1& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
			
		return HANDLED;
	}
	
	state_return_type visit(const Event2& e) override { 
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		//Self-transition
		return transition<State2>();
	}
};

int main() {	
	Event1 e1(10);
	Event2 e2;
	
	PRINT_STATEMENT(MyStateMachine sm;)
	sm.init();
	std::cout << std::endl;
	
	PRINT_STATEMENT(sm.dispatch(e1);)
	std::cout << std::endl;
	PRINT_STATEMENT(sm.dispatch(e2);)
	std::cout << std::endl;
	
	PRINT_STATEMENT(sm.dispatch(e1);)
	std::cout << std::endl;
	PRINT_STATEMENT(sm.dispatch(e2);)
	std::cout << std::endl;
		
	PRINT_STATEMENT(sm.dispatch(e1);)
	std::cout << std::endl;
	PRINT_STATEMENT(sm.dispatch(e2);)
	std::cout << std::endl;
	
	return 0;
}