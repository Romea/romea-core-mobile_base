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


#ifndef ROMEA_CORE_MOBILE_BASE__SIMULATION__SIMULATIONCONTROL2AS2FWD_HPP_
#define ROMEA_CORE_MOBILE_BASE__SIMULATION__SIMULATIONCONTROL2AS2FWD_HPP_

#include "romea_core_mobile_base/simulation/SimulationControl2ASxxx.hpp"
#include "romea_core_mobile_base/hardware/HardwareControl2AS2FWD.hpp"

namespace romea
{
namespace core
{

using SimulationCommand2AS2FWD = SimulationCommand2ASxxx;
using SimulationState2AS2FWD = SimulationState2ASxxx;

SimulationCommand2AS2FWD toSimulationCommand2AS2FWD(
  const double & wheelbase,
  const double & frontTrack,
  const double & frontWheelRadius,
  const double & frontHubCarrierOffset,
  const double & rearTrack,
  const double & rearWheelRadius,
  const double & rearHubCarrierOffset,
  const HardwareCommand2AS2FWD & hardwareCommand);

SimulationState2AS2FWD toSimulationState2AS2FWD(
  const double & wheelbase,
  const double & frontTrack,
  const double & frontWheelRadius,
  const double & frontHubCarrierOffset,
  const double & rearTrack,
  const double & rearWheelRadius,
  const double & rearHubCarrierOffset,
  const HardwareState2AS2FWD & hardwareCommand);

HardwareState2AS2FWD toHardwareState2AS2FWD(
  const double & wheelbase,
  const double & front_track,
  const double & rearTrack,
  const SimulationState2AS2FWD & simulationState);

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_MOBILE_BASE__SIMULATION__SIMULATIONCONTROL2AS2FWD_HPP_
