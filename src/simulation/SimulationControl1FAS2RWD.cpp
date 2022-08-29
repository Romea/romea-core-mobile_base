#include "romea_core_mobile_base/simulation/SimulationControl1FAS2RWD.hpp"
#include "romea_core_mobile_base/kinematic/skid_steering/SkidSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/wheel_steering/TwoWheelSteeringKinematic.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
SimulationCommand1FAS2RWD toSimulationCommand1FAS2RWD(const HardwareCommand1FAS2RWD & hardwareCommand,
                                                      const double & frontLeftWheelSteeringAngle,
                                                      const double & frontRightWheelSteeringAngle,
                                                      const double & frontLeftWheelSetPoint,
                                                      const double & frontRightWheelSetPoint)
{
  return {hardwareCommand.frontAxleSteeringAngle,
        frontLeftWheelSteeringAngle,
        frontRightWheelSteeringAngle,
        frontLeftWheelSetPoint,
        frontRightWheelSetPoint,
        hardwareCommand.rearLeftWheelSetPoint,
        hardwareCommand.rearRightWheelSetPoint};
}

//-----------------------------------------------------------------------------
SimulationCommand1FAS2RWD toSimulationCommand1FAS2RWD(const double & wheelbase,
                                                      const double & frontTrack,
                                                      const double & frontHubCarrierOffset,
                                                      const double & frontWheelRadius,
                                                      const double & rearWheelRadius,
                                                      const HardwareCommand1FAS2RWD & hardwareCommand)
{
  const double & rearLeftWheelLinearSpeed =
      hardwareCommand.rearLeftWheelSetPoint*rearWheelRadius;

  const double & rearRightWheelLinearSpeed =
      hardwareCommand.rearRightWheelSetPoint*rearWheelRadius;

  double  tanAxleSteeringAngle=
      std::tan(hardwareCommand.frontAxleSteeringAngle);

  double intantaneousCurvature= OneAxleSteeringKinematic::
      computeInstantaneousCurvature(tanAxleSteeringAngle,wheelbase);


  double frontLeftWheelSteeringAngle = TwoWheelSteeringKinematic::
      computeLeftWheelSteeringAngle(tanAxleSteeringAngle,
                                    intantaneousCurvature,
                                    frontTrack/2.);

  double frontRightWheelSteeringAngle = TwoWheelSteeringKinematic::
      computeRightWheelSteeringAngle(tanAxleSteeringAngle,
                                     intantaneousCurvature,
                                     frontTrack/2.);

  double linearSpeedCommand = (rearLeftWheelLinearSpeed + rearRightWheelLinearSpeed)/2.;

  double frontLeftWheelLinearSpeed = TwoWheelSteeringKinematic::
      computeLeftWheelLinearSpeed(linearSpeedCommand,
                                  tanAxleSteeringAngle,
                                  intantaneousCurvature,
                                  frontHubCarrierOffset,
                                  frontTrack/2.);

  double frontRightWheelLinearSpeed = TwoWheelSteeringKinematic::
      computeRightWheelLinearSpeed(linearSpeedCommand,
                                   tanAxleSteeringAngle,
                                   intantaneousCurvature,
                                   frontHubCarrierOffset,
                                   frontTrack/2.);



  return toSimulationCommand1FAS2RWD(hardwareCommand,
                                     frontLeftWheelSteeringAngle,
                                     frontRightWheelSteeringAngle,
                                     frontLeftWheelLinearSpeed/frontWheelRadius,
                                     frontRightWheelLinearSpeed/frontWheelRadius);
}

//-----------------------------------------------------------------------------
HardwareState1FAS2RWD toHardwareState1FAS2RWD(const SimulationState1FAS2RWD & simulationState,
                                              const double frontAxleSteeringAngle)
{
  return { frontAxleSteeringAngle,
        simulationState.rearLeftWheelSpinMotion,
        simulationState.rearRightWheelSpinMotion};

}

//-----------------------------------------------------------------------------
HardwareState1FAS2RWD toHardwareState1FAS2RWD(const double & wheelbase,
                                              const double & frontTrack,
                                              const SimulationState1FAS2RWD & simulationState)
{

  double frontAxleSteeringAngle = TwoWheelSteeringKinematic::
      computeSteeringAngle(simulationState.frontLeftWheelSteeringAngle,
                           simulationState.frontRightWheelSteeringAngle,
                           wheelbase,frontTrack);

  return toHardwareState1FAS2RWD(simulationState,
                                 frontAxleSteeringAngle);
}

}
