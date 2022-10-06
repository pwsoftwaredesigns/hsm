#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <functional>

using state_return_type = std::function<bool()>;

constexpr auto HANDLED = [](){ return true; };
constexpr auto PASS = [](){ return false; };

#endif //_COMMON_HPP_