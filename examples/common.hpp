#ifndef EXAMPLES_COMMON_HPP_
#define EXAMPLES_COMMON_HPP_

#include <iostream>
#include <cassert>

#define PRINT_STATEMENT(s_) std::cout << std::endl << "\033[1;32m" << #s_ << "\033[m" << std::endl; s_
#define PRINT_CURRENT_STATE(sm_) std::cout << "\033[1;34mCurrent State: " << sm_.currentStateName() << "\033[m" << std::endl
#define PRINT_TRACE() std::cout << __PRETTY_FUNCTION__ << std::endl

#endif //EXAMPLES_COMMON_HPP_