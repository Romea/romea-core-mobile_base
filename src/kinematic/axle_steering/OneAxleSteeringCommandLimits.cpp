﻿// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <ostream>

// romea
#include "romea_core_mobile_base/kinematic/axle_steering/OneAxleSteeringCommandLimits.hpp"
#include "romea_core_mobile_base/kinematic/CommandLimits.hpp"


namespace romea
{

//--------------------------------------------------------------------------
OneAxleSteeringCommandLimits::OneAxleSteeringCommandLimits()
: longitudinalSpeed(),
  steeringAngle(-M_PI_2, M_PI_2)
{
}

//--------------------------------------------------------------------------
OneAxleSteeringCommandLimits::OneAxleSteeringCommandLimits(
  const double & minimalLongitudinalSpeed,
  const double & maximalLongidudinalSpeed,
  const double & maximalSteeringAngle)
: longitudinalSpeed(makeLongitudinalSpeedCommandLimits(minimalLongitudinalSpeed,
    maximalLongidudinalSpeed)),
  steeringAngle(makeSteeringAngleCommandLimits(maximalSteeringAngle))
{
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const OneAxleSteeringCommandLimits & limits)
{
  os << "Command limits : " << std::endl;
  os << " longitudinal speed : [" <<
    limits.longitudinalSpeed.lower() << " " <<
    limits.longitudinalSpeed.upper() << "]" << std::endl;
  os << " stering angle : [" <<
    limits.steeringAngle.lower() << " " <<
    limits.steeringAngle.upper() << "]";
  return os;
}

}  // namespace romea
