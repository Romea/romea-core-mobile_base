// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// romea core
#include <romea_core_common/math/Algorithm.hpp>

// std
#include <cmath>
#include <limits>

// local
#include "romea_core_mobile_base/kinematic/wheel_steering/TwoWheelSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/axle_steering/OneAxleSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/skid_steering/SkidSteeringKinematic.hpp"

namespace romea
{
namespace core
{

//--------------------------------------------------------------------------
TwoWheelSteeringKinematic::Parameters::Parameters()
: frontWheelBase(0),
  rearWheelBase(0),
  frontWheelTrack(0),
  rearWheelTrack(0),
  frontHubCarrierOffset(0),
  rearHubCarrierOffset(0),
  frontMaximalWheelLinearSpeed(std::numeric_limits<double>::max()),
  rearMaximalWheelLinearSpeed(std::numeric_limits<double>::max()),
  maximalWheelLinearAcceleration(std::numeric_limits<double>::max()),
  maximalWheelSteeringAngle(M_PI_2),
  maximalWheelSteeringAngularSpeed(std::numeric_limits<double>::max()),
  wheelLinearSpeedVariance(0),
  wheelSteeringAngleVariance(0)
{
}


//--------------------------------------------------------------------------
double TwoWheelSteeringKinematic::computeInstantaneousCurvature(
  const double & leftInstantaneousCurvature,
  const double & rightInstantaneousCurvature,
  const double & track)
{
  return 0.5 * (leftInstantaneousCurvature / (1 + leftInstantaneousCurvature * track / 2) +
         rightInstantaneousCurvature / (1 - rightInstantaneousCurvature * track / 2));
}

//--------------------------------------------------------------------------
double TwoWheelSteeringKinematic::computeInstantaneousCurvature(
  const double & leftWheelSteeringAngle,
  const double & rightWheelSteeringAngle,
  const double & wheelbase,
  const double & track)
{
  double leftInstantaneousCurvature = OneAxleSteeringKinematic::
    computeInstantaneousCurvature(std::tan(leftWheelSteeringAngle), wheelbase);
  double rightInstantaneousCurvature = OneAxleSteeringKinematic::
    computeInstantaneousCurvature(std::tan(rightWheelSteeringAngle), wheelbase);

  return computeInstantaneousCurvature(
    leftInstantaneousCurvature,
    rightInstantaneousCurvature,
    track);
}

//--------------------------------------------------------------------------
double TwoWheelSteeringKinematic::computeSteeringAngle(
  const double & leftWheelSteeringAngle,
  const double & rightWheelSteeringAngle,
  const double & wheelbase,
  const double & track)
{
  double instantaneousCurvature = computeInstantaneousCurvature(
    leftWheelSteeringAngle,
    rightWheelSteeringAngle,
    wheelbase,
    track);

  return OneAxleSteeringKinematic::computeSteeringAngle(
    instantaneousCurvature,
    wheelbase);
}


//--------------------------------------------------------------------------
double TwoWheelSteeringKinematic::computeLeftWheelSteeringAngle(
  const double & tanSteeringAngle,
  const double & instantaneousCurvature,
  const double & halfTrack)
{
  return std::atan(tanSteeringAngle / (1 - instantaneousCurvature * halfTrack));
}

//--------------------------------------------------------------------------
double TwoWheelSteeringKinematic::computeRightWheelSteeringAngle(
  const double & tanSteeringAngle,
  const double & instantaneousCurvature,
  const double & halfTrack)
{
  return std::atan(tanSteeringAngle / (1 + instantaneousCurvature * halfTrack));
}

//--------------------------------------------------------------------------
double TwoWheelSteeringKinematic::computeMaximalInstantaneousCurvature(
  const double wheelbase,
  const double halfTrack,
  const double & maximalWheelSteeringAngle)
{
  double maximalAbsoluteIntantaneousCurvature = OneAxleSteeringKinematic::
    computeInstantaneousCurvature(std::tan(maximalWheelSteeringAngle), wheelbase);

  return maximalAbsoluteIntantaneousCurvature = maximalAbsoluteIntantaneousCurvature /
           (1 + maximalAbsoluteIntantaneousCurvature * halfTrack);
}


//--------------------------------------------------------------------------
OneAxleSteeringCommand clamp(
  const TwoWheelSteeringKinematic::Parameters & parameters,
  const OneAxleSteeringCommandLimits & userLimits,
  const OneAxleSteeringCommand & command)
{
  double wheelbase = parameters.rearWheelBase + parameters.frontWheelBase;

  double maximalInstantaneousCurvature = TwoWheelSteeringKinematic::
    computeMaximalInstantaneousCurvature(
    wheelbase,
    parameters.frontWheelTrack / 2.,
    parameters.maximalWheelSteeringAngle);

  return OneAxleSteeringKinematic::clamp(
    wheelbase,
    parameters.frontWheelTrack / 2.,
    parameters.rearWheelTrack / 2.,
    parameters.frontHubCarrierOffset,
    parameters.rearHubCarrierOffset,
    std::atan(maximalInstantaneousCurvature * wheelbase),
    parameters.frontMaximalWheelLinearSpeed,
    parameters.rearMaximalWheelLinearSpeed,
    userLimits,
    command);
}

//--------------------------------------------------------------------------
OneAxleSteeringCommand clamp(
  const TwoWheelSteeringKinematic::Parameters & parameters,
  const OneAxleSteeringCommand & previousCommand,
  const OneAxleSteeringCommand & currentCommand,
  const double & dt)
{
  double wheelbase = parameters.rearWheelBase + parameters.frontWheelBase;

  double tanSteeringAngle = std::tan(previousCommand.steeringAngle);
  double alpha = tanSteeringAngle * tanSteeringAngle;
  double beta = 1 + tanSteeringAngle * parameters.frontWheelTrack / (2 * wheelbase);

  double maximalSteeringAngularSpeed =
    parameters.maximalWheelSteeringAngularSpeed * (alpha + std::pow(beta, 2.)) / (1 + alpha);

  return OneAxleSteeringKinematic::clamp(
    wheelbase,
    parameters.frontWheelTrack / 2.,
    parameters.rearWheelTrack / 2.,
    parameters.frontHubCarrierOffset,
    parameters.rearHubCarrierOffset,
    maximalSteeringAngularSpeed,
    parameters.maximalWheelLinearAcceleration,
    previousCommand,
    currentCommand,
    dt);
}

}  // namespace core
}  // namespace romea

// old codes

// //--------------------------------------------------------------------------
// KinematicCommand clamp(
//   const KinematicCommand & command,
//   const TwoWheelSteeringKinematic & kinematic,
//   const KinematicConstraints & userLimits)
// {
//   //clamp curvature
//   double maximalAbsoluteIntantaneousCurvature = std::min(
//     kinematic.computeMaximalInstantaneousCurvature(),
//     userLimits.getMaximalAbsoluteInstantaneousCurvature());

//   double instantaneousCurvature = romea::clamp(
//     command.instantaneousCurvature,
//     -maximalAbsoluteIntantaneousCurvature,
//     maximalAbsoluteIntantaneousCurvature);

//   //clamp linear speed
//   const double wheelBase = kinematic.getWheelBase("wheelbase");
//   const double frontTrack = kinematic.getTrack("front_track");

//   double maximalAbsoluteLinearSpeed = std::numeric_limits<double>::max();

//   maximalAbsoluteLinearSpeed = std::min(
//     maximalAbsoluteLinearSpeed,
//     userLimits.getMaximalAbsoluteAngularSpeed() /
//     userLimits.getMaximalAbsoluteInstantaneousCurvature());

//   double maximalAbsoluteWheelAngle = std::atan(maximalAbsoluteIntantaneousCurvature * wheelBase);

//   maximalAbsoluteLinearSpeed = std::min(
//     maximalAbsoluteLinearSpeed,
//     kinematic.getMaximalWheelSpeed() * std::cos(maximalAbsoluteWheelAngle) /
//     (1 + maximalAbsoluteWheelAngle * frontTrack / 2));

//   double minimalSpeed = std::max(
//     userLimits.getMinimalSpeed(),
//     -maximalAbsoluteLinearSpeed);

//   double maximalSpeed = std::min(
//     userLimits.getMaximalSpeed(),
//     maximalAbsoluteLinearSpeed);

//   double linearSpeed = romea::clamp(
//     command.speed,
//     minimalSpeed,
//     maximalSpeed);

//   KinematicCommand clampedCommand;
//   clampedCommand.speed = linearSpeed;
//   clampedCommand.beta = 0;
//   clampedCommand.angularSpeed = instantaneousCurvature * linearSpeed;
//   clampedCommand.instantaneousCurvature = instantaneousCurvature;
//   return clampedCommand;

// }


// //--------------------------------------------------------------------------
// double maximalPermissibleLinearSpeed(
//   const TwoWheelSteeringKinematic::Parameters & parameters,
//   const double & instantaneousCurvature)
// {
//   double wheelbase = parameters.rearWheelBase + parameters.frontWheelBase;

//   double maximalInstantaneousCurvature = TwoWheelSteeringKinematic::
//     computeMaximalInstantaneousCurvature(
//     wheelbase,
//     parameters.frontTrack / 2.,
//     parameters.maximalWheelAngle);

//   double maximalVirtualSteeringAngle = std::atan(maximalInstantaneousCurvature * wheelbase);


//   double frontMaximalLinearSpeed = OneAxleSteeringKinematic::
//     maximalPermissibleLinearSpeed(
//     wheelbase,
//     parameters.frontTrack,
//     parameters.frontMaximalWheelSpeed,
//     maximalVirtualSteeringAngle,
//     parameters.frontHubCarrierOffset,
//     instantaneousCurvature);

//   double rearMaximalLinearSpeed = SkidSteeringKinematic::
//     maximalPermissibleLinearSpeed(
//     parameters.rearTrack + 2 * parameters.rearHubCarrierOffset,
//     parameters.rearMaximalWheelSpeed,
//     instantaneousCurvature);

//   return std::min(frontMaximalLinearSpeed, rearMaximalLinearSpeed);
// }

// //--------------------------------------------------------------------------
// double maximalPermissibleInstantaneousCurvature(
//   const TwoWheelSteeringKinematic::Parameters & parameters,
//   const double & linearSpeed)
// {

//   double wheelbase = parameters.rearWheelBase + parameters.frontWheelBase;

//   double maximalInstantaneousCurvature = TwoWheelSteeringKinematic::
//     computeMaximalInstantaneousCurvature(
//     wheelbase,
//     parameters.frontTrack / 2.,
//     parameters.maximalWheelAngle);

//   double maximalVirtualSteeringAngle = std::atan(maximalInstantaneousCurvature * wheelbase);

//   double frontMaximalInstantaneousCurvature = OneAxleSteeringKinematic::
//     maximalPermissibleInstantaneousCurvature(
//     wheelbase,
//     parameters.frontTrack,
//     parameters.frontMaximalWheelSpeed,
//     maximalVirtualSteeringAngle,
//     parameters.frontHubCarrierOffset,
//     linearSpeed);

//   double rearMaximalInstantaneousCurvature = SkidSteeringKinematic::
//     maximalPermissibleInstantaneousCurvature(
//     parameters.rearTrack + 2 * parameters.rearHubCarrierOffset,
//     parameters.rearMaximalWheelSpeed,
//     linearSpeed);

//   return std::min(frontMaximalInstantaneousCurvature, rearMaximalInstantaneousCurvature);

// }
