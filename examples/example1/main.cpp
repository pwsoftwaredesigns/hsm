#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>

#include "includes.hpp"

int main() {
	PRINT_STATEMENT(lamp::StateMachine sm;)
	PRINT_STATEMENT(sm.init());
	
	PRINT_STATEMENT(lamp::EPowerButtonPressed e;)
	
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "The lamp will burn up after being toggled " << lamp::MAX_TOGGLES << " times" << std::endl;	
	std::cout << "Press T+ENTER to TOGGLE the light" << std::endl;
	std::cout << "Press X+ENTER to EXIT" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;
		
	char c = ' ';
		
	while(c != 'X') {
		std::cin >> c;
		if (c == 'T') {
			PRINT_STATEMENT(sm.dispatch(e);)
		}
	}
	
	/*
	PRINT_STATEMENT(sm.dispatch(e);)
	PRINT_STATEMENT(sm.dispatch(e);)
	PRINT_STATEMENT(sm.dispatch(e);)
	PRINT_STATEMENT(sm.dispatch(e);)
	*/
	
	PRINT_STATEMENT(sm.deinit());

	return 0;
}