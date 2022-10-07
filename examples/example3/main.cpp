#include "StateMachine.hpp"

int main() {
	PRINT_STATEMENT(lamp::StateMachine sm;)
	PRINT_STATEMENT(sm.init());
	
	PRINT_STATEMENT(lamp::EPowerButtonPressed e;)
	PRINT_STATEMENT(sm.dispatch(e);)
	PRINT_STATEMENT(sm.dispatch(e);)
	
	PRINT_STATEMENT(sm.deinit());

	return 0;
}