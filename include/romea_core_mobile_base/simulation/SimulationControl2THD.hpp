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


#ifndef ROMEA_CORE_MOBILE_BASE__SIMULATION__SIMULATIONCONTROL2THD_HPP_
#define ROMEA_CORE_MOBILE_BASE__SIMULATION__SIMULATIONCONTROL2THD_HPP_

#include "romea_core_mobile_base/hardware/HardwareControl2TD.hpp"

namespace romea
{
namespace core
{

struct SimulationCommand2THD
{
  RotationalMotionCommand leftSprocketWheelSpinningSetPoint;
  RotationalMotionCommand rightSprocketWheelSpinningSetPoint;

  RotationalMotionCommand frontLeftIdlerWheelSpinningSetPoint;
  RotationalMotionCommand frontRightIdlerWheelSpinningSetPoint;
  RotationalMotionCommand rearLeftIdlerWheelSpinningSetPoint;
  RotationalMotionCommand rearRightIdlerWheelSpinningSetPoint;
};

std::ostream & operator<<(std::ostream & os, const SimulationCommand2THD & state);

struct SimulationState2THD
{
  RotationalMotionState leftSprocketWheelSpinningMotion;
  RotationalMotionState rightSprocketWheelSpinningMotion;

  RotationalMotionState frontLeftIdlerWheelSpinningMotion;
  RotationalMotionState frontRightIdlerWheelSpinningMotion;
  RotationalMotionState rearLeftIdlerWheelSpinningMotion;
  RotationalMotionState rearRightIdlerWheelSpinningMotion;
};

std::ostream & operator<<(std::ostream & os, const SimulationCommand2THD & state);

SimulationCommand2THD toSimulationCommand2THD(
  const double & sprocketWheelRadius,
  const double & idlerWheelRadius,
  const double & trackThickness,
  const HardwareCommand2TD & hardwareCommand);

SimulationState2THD toSimulationState2THD(
  const double & sprocketWheelRadius,
  const double & idlerWheelRadius,
  const double & trackThickness,
  const HardwareState2TD & hardwareState);

HardwareState2TD toHardwareState2TD(
  const double & sprocketWheelRadius,
  const double & idlerWheelRadius,
  const double & trackThickness,
  const SimulationState2THD & simulationState);

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_MOBILE_BASE__SIMULATION__SIMULATIONCONTROL2THD_HPP_
