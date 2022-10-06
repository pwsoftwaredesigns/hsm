#ifndef PW_HSM_FIRST_OF_HPP_
#define PW_HSM_FIRST_OF_HPP_

//-----[ TEMPLATE CLASS: first_of ]---------------------------------------------
/**
* @brief Find the first type in a type list
*/
template <typename ... TYPES>
struct first_of;

template <typename T, typename ... TYPES>
struct first_of<T, TYPES...> {
	using type = T;
};

template<>
struct first_of<> {
	using type = void;
};

template <typename ... TYPES>
using first_of_t = typename first_of<TYPES...>::type;

#endif //PW_HSM_FIRST_OF_HPP_