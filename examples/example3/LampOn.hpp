#ifndef EXAMPLES_EXAMPLE3_LAMPON_HPP_
#define EXAMPLES_EXAMPLE3_LAMPON_HPP_

#include "common.hpp"

namespace lamp {

PW_HSM_STATE(StateMachine, LampOn, Lamp)
{
public:
	LampOn(parent_type& parent);
	~LampOn();
	::pw::hsm::state_return_type visit(const EPowerButtonPressed& e) override;
};

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_LAMPON_HPP_