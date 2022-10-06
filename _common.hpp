#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <functional>
#include <iostream>

using state_return_type = std::function<bool()>;

constexpr auto HANDLED = [](){ std::cout << "\033[1;33mHANDLED\033[m" << std::endl; return true; };
constexpr auto PASS = [](){ std::cout << "\033[1;33mPASS\033[m" << std::endl; return false; };

template<typename T>
struct state_machine_traits;

#endif //_COMMON_HPP_