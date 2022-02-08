#include "romea_core_mobile_base/info/MobileBaseInfo1FAS2RWD.hpp"

namespace romea {

//-----------------------------------------------------------------------------
MobileBaseInfo1FAS2RWD::MobileBaseInfo1FAS2RWD():
  geometry(),
  frontAxleSteeringControl(),
  rearWheelsSpeedControl(),
  controlPoint(Eigen::Vector3d::Zero())
{

}

//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const MobileBaseInfo1FAS2RWD & baseInformation)
{
  os << "Base information:" << std::endl;
  os << " type:" << std::endl;
  os << "  1FAS2RWD"<<std::endl;
  os << " geometry:";
  os << baseInformation.geometry<< std::endl;
  os << " front axle steering control:" <<std::endl;
  os << baseInformation.frontAxleSteeringControl<< std::endl;
  os << " rear wheels speed control: " <<std::endl;
  os << baseInformation.rearWheelsSpeedControl<< std::endl;
  os << " intertia:" << std::endl;
  os << baseInformation.inertia;
  os << " control point:" << std::endl;
  os << "  " << baseInformation.controlPoint << std::endl;
  return os;
}

//-----------------------------------------------------------------------------
void to_kinematic_parameters(const MobileBaseInfo1FAS2RWD & baseInformation,
                             OneAxleSteeringKinematic::Parameters & kinematicParameters )
{
  const auto & geometry= baseInformation.geometry;
  const auto & wheelsSpeedCommand = baseInformation.rearWheelsSpeedControl.command;
  const auto & wheelsSpeedSensor = baseInformation.rearWheelsSpeedControl.sensor;
  const auto & axleSteeringCommand = baseInformation.frontAxleSteeringControl.command;
  const auto & axleSteeringSensor = baseInformation.frontAxleSteeringControl.sensor;
  const auto & controlPoint = baseInformation.controlPoint;

  kinematicParameters.frontWheelBase = geometry.wheelbase/2. - controlPoint.x();
  kinematicParameters.rearWheelBase = geometry.wheelbase/2.+ controlPoint.x();
  kinematicParameters.frontWheelTrack=geometry.frontAxle.wheelTrack;
  kinematicParameters.rearWheelTrack=geometry.rearAxle.wheelTrack;
  kinematicParameters.frontHubCarrierOffset = geometry.frontAxle.wheels.hubCarrierOffset;
  kinematicParameters.rearHubCarrierOffset = geometry.rearAxle.wheels.hubCarrierOffset;
  kinematicParameters.maximalSteeringAngle = axleSteeringCommand.maximalAngle;
  kinematicParameters.maximalSteeringAngularSpeed = axleSteeringCommand.maximalAngularSpeed;
  kinematicParameters.rearMaximalWheelSpeed = wheelsSpeedCommand.maximalSpeed;
  kinematicParameters.maximalWheelAcceleration = wheelsSpeedCommand.maximalAcceleration;
  kinematicParameters.wheelSpeedVariance = std::pow(wheelsSpeedSensor.speedStd,2.0);
  kinematicParameters.steeringAngleVariance = std::pow(axleSteeringSensor.angleStd,2.0);
}

}
