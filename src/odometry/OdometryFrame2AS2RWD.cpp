// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <ostream>

// romea
#include "romea_core_mobile_base/odometry/OdometryFrame2AS2RWD.hpp"

namespace romea
{

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & s, const OdometryFrame2AS2RWD & frame)
{
  s << "frontAxleSteeringAngle : " << frame.frontAxleSteeringAngle << std::endl;
  s << "rearAxleSteeringAngle : " << frame.rearAxleSteeringAngle << std::endl;
  s << "rearLeftWheelLinearSpeed : " << frame.rearLeftWheelLinearSpeed << std::endl;
  s << "rearRightWheelLinearSpeed : " << frame.rearRightWheelLinearSpeed << std::endl;
  return s;
}

}  // namespace romea
