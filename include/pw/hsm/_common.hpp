#ifndef PW_HSM__COMMON_HPP_
#define PW_HSM__COMMON_HPP_

#include <functional>
#include <ctti/detail/cstring.hpp>

#ifndef PW_HSM_TRANSITION_TRACE
	#define PW_HSM_TRANSITION_TRACE(source_, dest_) (void)0
#endif

#ifndef PW_HSM_HANDLED_TRACE
	#define PW_HSM_HANDLED_TRACE(...) (void)0
#endif

#ifndef PW_HSM_PASS_TRACE
	#define PW_HSM_PASS_TRACE(...) (void)0
#endif

#ifndef PW_HSM_USE_ETL
	#define PW_HSM_USE_ETL 1
#endif

namespace pw::hsm {

using name_string_type = ctti::detail::cstring;
using state_return_type = std::function<bool()>;

constexpr auto HANDLED = [](){ PW_HSM_HANDLED_TRACE(); return true; };
constexpr auto PASS = [](){ PW_HSM_PASS_TRACE(); return false; };

//template<typename T>
//struct state_machine_traits;

} //namespace pw::hsm


#endif //PW_HSM__COMMON_HPP_