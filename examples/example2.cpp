#include "common.hpp"

//******************************************************************************
//******************************************************************************

using namespace pw::hsm;

constexpr int A = 10;
constexpr int B = 20;

//******************************************************************************
//******************************************************************************

//Must forward-declare all states
class Root;
class State1;
class State11;
class State12;
class State2;
class State21;
class State22;
class MyStateMachine;

//Use helper macro to generate boiler-plate code for state machine
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
		PRINT_TRACE();
	}
	
	~MyStateMachine() 
	{
		//deinit();
		PRINT_TRACE();
	}
	
public:
	int a;
	int b;
};

//-----[ CLASS: Root ]----------------------------------------------------------
class Root :
	public ::pw::hsm::State<Root, MyStateMachine, State1, State2>
{
public:
	Root(parent_type& parent) :
		State(parent)
	{
		PRINT_TRACE();
			
		//The following lines shall result in a compilation error
		//deinit();
		//init();
		
		assert(root().a == A);
		assert(root().b == B);
	}
	
	~Root() {
		PRINT_TRACE();
	}
	
public:
	::pw::hsm::return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return HANDLED;
	}
	
	::pw::hsm::return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return HANDLED;
	}
	
public:
	int foo;
};

//-----[ CLASS: State1 ]--------------------------------------------------------
class State1 :
	public ::pw::hsm::State<State1, Root, State11, State12>
{
public:
	State1(parent_type& parent) :
		State(parent)
	{
		PRINT_TRACE();
	}
	
	~State1() {
		PRINT_TRACE();
	}
	
	::pw::hsm::return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
	::pw::hsm::return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
public:
	int publicVariable;
	
private:
	int _privateVariable;
};

//-----[ CLASS: State11 ]-------------------------------------------------------
class State11 :
	public ::pw::hsm::State<State11, State1>
{
public:
	State11(parent_type& parent) : 
		State(parent) 
	{
		PRINT_TRACE();
	}
	
	~State11() {
		PRINT_TRACE();
	}
	
public:
	::pw::hsm::return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		parent().publicVariable = e.arg();
		return PASS;
	}
	
	::pw::hsm::return_type visit(const Event2& e) override { 
		PRINT_TRACE();

		//Transition to sibling state
		return transition<State12>();
	}
};

//-----[ CLASS: State12 ]-------------------------------------------------------
class State12 :
	public ::pw::hsm::State<State12, State1>
{
public:
	State12(parent_type& parent) : 
		State(parent) 
	{
		PRINT_TRACE();
			
		++root().a;
		++root().b;
	}
	
	~State12() {
		PRINT_TRACE();
	}
	
public:
	::pw::hsm::return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		
		parent<Root>().foo = e.arg();
			
		return PASS;
	}
	
	::pw::hsm::return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return transition<State22>();
	}
};

//-----[ CLASS: State2 ]--------------------------------------------------------
class State2 :
	public ::pw::hsm::State<State2, Root, State21, State22>
{
public:
	State2(parent_type& parent) :
		State(parent)
	{
		PRINT_TRACE();
	}
	
	~State2() {
		PRINT_TRACE();
	}
	
	::pw::hsm::return_type visit(const Event1& e) override { 
		PRINT_TRACE();
			
		return HANDLED;
	}
	
	::pw::hsm::return_type visit(const Event2& e) override { 
		PRINT_TRACE();

		//Self-transition
		return transition<State2>();
	}
};

DEFINE_BASIC_STATE(State21, State2, (Event1, Event2));
DEFINE_BASIC_STATE(State22, State2, (Event1, Event2));

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
	
	sm.deinit();
	
	return 0;
}