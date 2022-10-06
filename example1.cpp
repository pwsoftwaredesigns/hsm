#include <iostream>
#include <cassert>
#include "includes.hpp"

#define PRINT_STATEMENT(s_) std::cout << "\033[1;32m" << #s_ << "\033[m" << std::endl; s_
	
#define DEFINE_BASIC_STATE(name_, parent_, ...)\
	class name_ :\
		public State<name_, parent_, ##__VA_ARGS__>\
	{\
	public:\
		name_(parent_type& parent) :\
			State(parent)\
		{\
			std::cout << __PRETTY_FUNCTION__ << std::endl;\
		}\
		\
		~name_() {\
			std::cout << __PRETTY_FUNCTION__ << std::endl;\
		}\
		\
		state_return_type visit(const Event1& e) override {\
			std::cout << __PRETTY_FUNCTION__ << std::endl;\
			return PASS;\
		}\
		\
		state_return_type visit(const Event2& e) override {\
			std::cout << __PRETTY_FUNCTION__ << std::endl;\
			return PASS;\
		}\
	}
	
	
#define PRINT_CURRENT_STATE(sm_) std::cout << "\033[1;34mCurrent State: " << sm_.currentStateName() << "\033[m" << std::endl << std::endl
	
//******************************************************************************
//******************************************************************************

constexpr int A = 10;
constexpr int B = 20;

//******************************************************************************
//******************************************************************************

class Root;
class State1;
class State11;
class State12;
class State2;
class State21;
class State22;
class MyStateMachine;

STATE_MACHINE(
	MyStateMachine, 
	Root,
	(Event1, int),
	(Event2)
) {
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
		return transition<State22>();
	}
};

//-----[ CLASS: State2 ]--------------------------------------------------------
class State2 :
	public State<State2, Root, State21, State22>
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

DEFINE_BASIC_STATE(State21, State2);
DEFINE_BASIC_STATE(State22, State2);

int main() {	
	Event1 e1(10);
	Event2 e2;
	
	PRINT_STATEMENT(MyStateMachine sm;)
	sm.init();
	PRINT_CURRENT_STATE(sm);
	
	PRINT_STATEMENT(sm.dispatch(e1);)
	PRINT_CURRENT_STATE(sm);
	PRINT_STATEMENT(sm.dispatch(e2);)
	PRINT_CURRENT_STATE(sm);
	
	PRINT_STATEMENT(sm.dispatch(e1);)
	PRINT_CURRENT_STATE(sm);
	PRINT_STATEMENT(sm.dispatch(e2);)
	PRINT_CURRENT_STATE(sm);
		
	PRINT_STATEMENT(sm.dispatch(e1);)
	PRINT_CURRENT_STATE(sm);
	PRINT_STATEMENT(sm.dispatch(e2);)
	PRINT_CURRENT_STATE(sm);
	
	return 0;
}