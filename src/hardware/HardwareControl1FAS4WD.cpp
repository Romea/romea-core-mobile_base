// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#include "romea_core_mobile_base/hardware/HardwareControl1FAS4WD.hpp"

namespace romea {

//------------------------------------------------------------------------------
std::ostream & operator<<(std::ostream &os, const HardwareCommand1FAS4WD & command)
{
  os << " Hardware1FAS4WD command : " << std::endl;
  os << " front axle steering angle : ";
  os << command.frontAxleSteeringAngle << std::endl;
  os << " front left wheel spinning setpoint : ";
  os << command.frontLeftWheelSpinningSetPoint << std::endl;
  os << " front right wheel spinning setpoint : ";
  os << command.frontRightWheelSpinningSetPoint << std::endl;
  os << " rear left wheel spinning setpoint : ";
  os << command.rearLeftWheelSpinningSetPoint << std::endl;
  os << " rear right wheel spinning setpoint : ";
  os << command.rearRightWheelSpinningSetPoint;
  return os;
}

//------------------------------------------------------------------------------
std::ostream & operator<<(std::ostream &os, const HardwareState1FAS4WD & state)
{
  os << " Hardware1FAS4WD state : "<< std::endl;
  os << " front axle steering angle : ";
  os << state.frontAxleSteeringAngle << std::endl;
  os << " front left wheel spinning motion: ";
  os << state.frontLeftWheelSpinningMotion << std::endl;
  os << " front right wheel spinning motion : ";
  os << state.frontRightWheelSpinningMotion << std::endl;
  os << " rear left wheel spinning motion: ";
  os << state.rearLeftWheelSpinningMotion << std::endl;
  os << " rear right wheel spinning motion : ";
  os << state.rearRightWheelSpinningMotion ;
  return os;
}

}  // namespace romea
