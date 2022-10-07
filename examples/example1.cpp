#include "common.hpp"

using namespace pw::hsm;

//Must forward-declare all states
class Root;
class State1;
class State11;
class State12;
class State2;
class State21;
class State22;
class MyStateMachine;

//-----[ STATE MACHINE: MyStateMachine ]----------------------------------------
//Use helper macro to generate boiler-plate code for state machine
STATE_MACHINE(
	MyStateMachine, 
	Root,
	(Event1),
	(Event2)
) {
public:
	MyStateMachine()
	{
		PRINT_TRACE();
	}
	
	~MyStateMachine() 
	{
		PRINT_TRACE();
	}
};

//-----[ STATE: Root ]----------------------------------------------------------
class Root : public ::pw::hsm::State<Root, MyStateMachine, State1, State2>
{
public:
	Root(parent_type& parent) :
		State(parent)
	{
		PRINT_TRACE();
	}
	
	~Root() {
		PRINT_TRACE();
	}
	
public:
	::pw::hsm::state_return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return HANDLED;
	}
	
	::pw::hsm::state_return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return HANDLED;
	}
}; //class Root

//-----[ STATE: State1 ]--------------------------------------------------------
class State1 : public ::pw::hsm::State<State1, Root, State11, State12>
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
	
public:
	::pw::hsm::state_return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
	::pw::hsm::state_return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return PASS;
	}
}; //class State1

//-----[ STATE: State11 ]--------------------------------------------------------
class State11 : public ::pw::hsm::State<State11, State1>
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
	::pw::hsm::state_return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
	::pw::hsm::state_return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return PASS;
	}
}; //class State11

//-----[ STATE: State12 ]--------------------------------------------------------
class State12 : public ::pw::hsm::State<State12, State1>
{
public:
	State12(parent_type& parent) :
		State(parent)
	{
		PRINT_TRACE();
	}
	
	~State12() {
		PRINT_TRACE();
	}
	
public:
	::pw::hsm::state_return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
	::pw::hsm::state_return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return PASS;
	}
}; //class State12

//-----[ STATE: State2 ]--------------------------------------------------------
class State2 : public ::pw::hsm::State<State2, Root, State21, State22>
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
	
public:
	::pw::hsm::state_return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
	::pw::hsm::state_return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return PASS;
	}
}; //class State2

//-----[ STATE: State21 ]--------------------------------------------------------
class State21 : public ::pw::hsm::State<State21, State2>
{
public:
	State21(parent_type& parent) :
		State(parent)
	{
		PRINT_TRACE();
	}
	
	~State21() {
		PRINT_TRACE();
	}
	
public:
	::pw::hsm::state_return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
	::pw::hsm::state_return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return PASS;
	}
}; //class State21

//-----[ STATE: State22 ]--------------------------------------------------------
class State22 : public ::pw::hsm::State<State22, State2>
{
public:
	State22(parent_type& parent) :
		State(parent)
	{
		PRINT_TRACE();
	}
	
	~State22() {
		PRINT_TRACE();
	}
	
public:
	::pw::hsm::state_return_type visit(const Event1& e) override { 
		PRINT_TRACE();
		return PASS;
	}
	
	::pw::hsm::state_return_type visit(const Event2& e) override { 
		PRINT_TRACE();
		return PASS;
	}
}; //class State22

int main() {	
	Event1 e1;
	Event2 e2;
	
	PRINT_STATEMENT(MyStateMachine sm;)
	sm.init();
	PRINT_CURRENT_STATE(sm);
	
	PRINT_STATEMENT(sm.dispatch(e1);)
	PRINT_CURRENT_STATE(sm);
	PRINT_STATEMENT(sm.dispatch(e2);)
	PRINT_CURRENT_STATE(sm);
	
	sm.deinit();
	
	return 0;
}