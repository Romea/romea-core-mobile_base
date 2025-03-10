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


#include "romea_core_mobile_base/simulation/SimulationControl1FAS2FWD.hpp"
#include "romea_core_mobile_base/kinematic/skid_steering/SkidSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/wheel_steering/TwoWheelSteeringKinematic.hpp"

namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
SimulationCommand1FAS2FWD toSimulationCommand1FAS2FWD(
  const HardwareCommand1FAS2FWD & hardwareCommand,
  const double & frontLeftWheelSteeringAngleCommand,
  const double & frontRightWheelSteeringAngleCommand,
  const double & rearLeftWheelAngularSpeedCommand,
  const double & rearRightWheelAngularSpeedCommand)
{
  return {hardwareCommand.frontAxleSteeringAngle,
    frontLeftWheelSteeringAngleCommand,
    frontRightWheelSteeringAngleCommand,
    hardwareCommand.frontLeftWheelSpinningSetPoint,
    hardwareCommand.frontRightWheelSpinningSetPoint,
    rearLeftWheelAngularSpeedCommand,
    rearRightWheelAngularSpeedCommand};
}

//-----------------------------------------------------------------------------
SimulationCommand1FAS2FWD toSimulationCommand1FAS2FWD(
  const double & wheelbase,
  const double & frontTrack,
  const double & rearTrack,
  const double & frontWheelRadius,
  const double & rearWheelRadius,
  const double & frontHubCarrierOffset,
  const double & rearHubCarrierOffset,
  const HardwareCommand1FAS2FWD & hardwareCommand)
{
  double fullRearTrack = rearTrack + 2 * rearHubCarrierOffset;

  const double & frontLeftWheelLinearSpeed =
    hardwareCommand.frontLeftWheelSpinningSetPoint * frontWheelRadius;

  const double & frontRightWheelLinearSpeed =
    hardwareCommand.frontRightWheelSpinningSetPoint * frontWheelRadius;

  const double & tanAxleSteeringAngle =
    std::tan(hardwareCommand.frontAxleSteeringAngle);

  double instantaneousCurvature = OneAxleSteeringKinematic::
    computeInstantaneousCurvature(tanAxleSteeringAngle, wheelbase);


  double frontLeftWheelSteeringAngle = TwoWheelSteeringKinematic::
    computeLeftWheelSteeringAngle(
    tanAxleSteeringAngle,
    instantaneousCurvature,
    frontTrack / 2.);

  double frontRightWheelSteeringAngle = TwoWheelSteeringKinematic::
    computeRightWheelSteeringAngle(
    tanAxleSteeringAngle,
    instantaneousCurvature,
    frontTrack / 2.);


  double linearSpeed = 0.5 * (frontLeftWheelLinearSpeed / TwoWheelSteeringKinematic::
    computeWheelLinearSpeedRatio(
      -tanAxleSteeringAngle,
      -instantaneousCurvature,
      frontHubCarrierOffset,
      frontTrack / 2.) +
    frontRightWheelLinearSpeed / TwoWheelSteeringKinematic::
    computeWheelLinearSpeedRatio(
      tanAxleSteeringAngle,
      instantaneousCurvature,
      frontHubCarrierOffset,
      frontTrack / 2.));

  double angularSpeed = instantaneousCurvature * linearSpeed;

  double rearLeftWheelLinearSpeed = SkidSteeringKinematic::
    computeLeftWheelLinearSpeed(linearSpeed, angularSpeed, fullRearTrack);

  double rearRightWheelLinearSpeed = SkidSteeringKinematic::
    computeRightWheelLinearSpeed(linearSpeed, angularSpeed, fullRearTrack);

  return toSimulationCommand1FAS2FWD(
    hardwareCommand,
    frontLeftWheelSteeringAngle,
    frontRightWheelSteeringAngle,
    rearLeftWheelLinearSpeed / rearWheelRadius,
    rearRightWheelLinearSpeed / rearWheelRadius);
}

//-----------------------------------------------------------------------------
SimulationState1FAS2FWD toSimulationState1FAS2FWD(
  const double & wheelbase,
  const double & frontTrack,
  const double & rearTrack,
  const double & frontWheelRadius,
  const double & rearWheelRadius,
  const double & frontHubCarrierOffset,
  const double & rearHubCarrierOffset,
  const HardwareState1FAS2FWD & hardwareState)
{
  core::HardwareCommand1FAS2FWD fakeHardwareCommand = {
    hardwareState.frontAxleSteeringAngle,
    hardwareState.frontLeftWheelSpinningMotion.velocity,
    hardwareState.frontRightWheelSpinningMotion.velocity
  };

  SimulationCommand1FAS2FWD fakeSimulationCommand = toSimulationCommand1FAS2FWD(
    wheelbase,
    frontTrack,
    rearTrack,
    frontWheelRadius,
    rearWheelRadius,
    frontHubCarrierOffset,
    rearHubCarrierOffset,
    fakeHardwareCommand);

  SimulationState1FAS2FWD simulationState;
  simulationState.frontAxleSteeringAngle =
    hardwareState.frontAxleSteeringAngle;
  simulationState.frontLeftWheelSteeringAngle =
    fakeSimulationCommand.frontLeftWheelSteeringAngle;
  simulationState.frontRightWheelSteeringAngle =
    fakeSimulationCommand.frontRightWheelSteeringAngle;
  simulationState.frontLeftWheelSpinningMotion =
    hardwareState.frontLeftWheelSpinningMotion;
  simulationState.frontRightWheelSpinningMotion =
    hardwareState.frontRightWheelSpinningMotion;
  simulationState.rearLeftWheelSpinningMotion.velocity =
    fakeSimulationCommand.rearLeftWheelSpinningSetPoint;
  simulationState.rearRightWheelSpinningMotion.velocity =
    fakeSimulationCommand.rearRightWheelSpinningSetPoint;

  return simulationState;
}

//-----------------------------------------------------------------------------
HardwareState1FAS2FWD toHardwareState1FAS2FWD(
  const SimulationState1FAS2FWD & simulationState,
  const double frontAxleSteeringAngle)
{
  return {frontAxleSteeringAngle,
    simulationState.frontLeftWheelSpinningMotion,
    simulationState.frontRightWheelSpinningMotion};
}

//-----------------------------------------------------------------------------
HardwareState1FAS2FWD toHardwareState1FAS2FWD(
  const double & wheelbase,
  const double & frontTrack,
  const SimulationState1FAS2FWD & simulationState)
{
  double frontAxleSteeringAngle = TwoWheelSteeringKinematic::
    computeSteeringAngle(
    simulationState.frontLeftWheelSteeringAngle,
    simulationState.frontRightWheelSteeringAngle,
    wheelbase, frontTrack);

  return toHardwareState1FAS2FWD(simulationState, frontAxleSteeringAngle);
}

}  // namespace core
}  // namespace romea
