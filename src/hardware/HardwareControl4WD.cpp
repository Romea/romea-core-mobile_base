#include "romea_core_mobile_base/hardware/HardwareControl4WD.hpp"

namespace romea {

//------------------------------------------------------------------------------
std::ostream & operator<<(std::ostream &os, const HardwareCommand4WD & command)
{
  os << " Hardware4WD command : " <<std::endl;
  os << " front left wheel setpoint : " << command.frontLeftWheelSetPoint << std::endl;
  os << " front right wheel setpoint : " << command.frontRightWheelSetPoint  << std::endl;
  os << " rear left wheel setpoint : " << command.rearLeftWheelSetPoint  << std::endl;
  os << " rear right wheel setpoint : " << command.rearRightWheelSetPoint  ;
  return os;
}

//------------------------------------------------------------------------------
std::ostream & operator<<(std::ostream &os, const HardwareState4WD & state)
{
  os << " Hardware4WD state : " << std::endl;
  os << " front left wheel spin motion : " << state.frontLeftWheelSpinMotion << std::endl;
  os << " front right wheel spin motion : " << state.frontRightWheelSpinMotion << std::endl;
  os << " rear left wheel spin motion : " << state.rearLeftWheelSpinMotion << std::endl;
  os << " rear right wheel spin motion : " << state.rearRightWheelSpinMotion ;
  return os;
}

}//end romea
