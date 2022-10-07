#ifndef EXAMPLES_COMMON_HPP_
#define EXAMPLES_COMMON_HPP_

#include <iostream>
#include <cassert>
#include <pw/hsm/includes.hpp>
#include <map.h>

#define PRINT_STATEMENT(s_) std::cout << "\033[1;32m" << #s_ << "\033[m" << std::endl; s_
#define PRINT_CURRENT_STATE(sm_) std::cout << "\033[1;34mCurrent State: " << sm_.currentStateName() << "\033[m" << std::endl << std::endl
#define PRINT_TRACE() std::cout << __PRETTY_FUNCTION__ << std::endl

#define DEFINE_BASIC_STATE(name_, parent_, events_, ...)\
	class name_ :\
		public ::pw::hsm::State<name_, parent_, ##__VA_ARGS__>\
	{\
	public:\
		name_(parent_type& parent) :\
			State(parent)\
		{\
			PRINT_TRACE();\
		}\
		\
		~name_() {\
			PRINT_TRACE();\
		}\
		\
		_DEFINE_BASIC_STATE_VISITORS(events_)\
	}
	
#define _DEFINE_BASIC_STATE_VISITORS(events_) _DEFINE_BASIC_STATE_VISITORSX events_
#define _DEFINE_BASIC_STATE_VISITORSX(...) MAP(_DEFINE_BASIC_STATE_VISITOR, ##__VA_ARGS__)
#define _DEFINE_BASIC_STATE_VISITOR(e_)\
	::pw::hsm::state_return_type visit(const e_& e) override {\
		PRINT_TRACE();\
		return PASS;\
	}

#endif //EXAMPLES_COMMON_HPP_