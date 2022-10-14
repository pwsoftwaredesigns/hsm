#ifndef EXAMPLES_EXAMPLE3_LAMPDEAD_HPP_
#define EXAMPLES_EXAMPLE3_LAMPDEAD_HPP_

#include "common.hpp"

namespace lamp {

PW_HSM_STATE(StateMachine, LampDead, Lamp)
{
public:
	LampDead(parent_type& parent);
	~LampDead();
	::pw::hsm::return_type visit(const EPowerButtonPressed& e) override;
};

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_LAMPDEAD_HPP_