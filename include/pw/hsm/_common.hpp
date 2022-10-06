#ifndef PW_HSM__COMMON_HPP_
#define PW_HSM__COMMON_HPP_

#include <functional>
#include <iostream>
#include <ctti/detail/cstring.hpp>

namespace pw::hsm {

using name_string_type = ctti::detail::cstring;
using state_return_type = std::function<bool()>;

constexpr auto HANDLED = [](){ std::cout << "\033[1;33mHANDLED\033[m" << std::endl; return true; };
constexpr auto PASS = [](){ std::cout << "\033[1;33mPASS\033[m" << std::endl; return false; };

//template<typename T>
//struct state_machine_traits;

} //namespace pw::hsm


#endif //PW_HSM__COMMON_HPP_