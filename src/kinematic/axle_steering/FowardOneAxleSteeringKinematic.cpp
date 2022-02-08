//romea
#include "romea_core_mobile_base/kinematic/axle_steering/FowardOneAxleSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/axle_steering/OneAxleSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/skid_steering/SkidSteeringKinematic.hpp"

#include <iostream>

namespace romea {

//-----------------------------------------------------------------------------
void forwardKinematic(const OneAxleSteeringKinematic::Parameters &parameters,
                      const OneAxleSteeringCommand & commandFrame,
                      OdometryFrame1FAS2FWD &odometryCommandFrame)
{
  const double halfWheelTrack = parameters.frontWheelTrack/2.;
  const double wheelBase=  parameters.frontWheelBase+parameters.rearWheelBase;
  const double hubCarrierOffset = parameters.frontHubCarrierOffset;

  const double & linearSpeed = commandFrame.longitudinalSpeed;
  const double & steeringAngle = commandFrame.steeringAngle;
  double tanSteeringAngle = std::tan(steeringAngle);
  double instantaneousCurvature = tanSteeringAngle/wheelBase;

  double frontLeftWheelSpeed=OneAxleSteeringKinematic::computeLeftWheelSpeed(linearSpeed,
                                                                             tanSteeringAngle,
                                                                             instantaneousCurvature,
                                                                             hubCarrierOffset,
                                                                             halfWheelTrack);



  double frontRightWheelSpeed=OneAxleSteeringKinematic::computeRightWheelSpeed(linearSpeed,
                                                                               tanSteeringAngle,
                                                                               instantaneousCurvature,
                                                                               hubCarrierOffset,
                                                                               halfWheelTrack);

  odometryCommandFrame.frontAxleSteeringAngle=steeringAngle;
  odometryCommandFrame.frontLeftWheelSpeed=frontLeftWheelSpeed;
  odometryCommandFrame.frontRightWheelSpeed=frontRightWheelSpeed;

}

////-----------------------------------------------------------------------------
//OdometryFrame1FAS2FWD forwardKinematic1FAS2FWD(const std::string &emitterName,
//                                               const OneAxleSteeringKinematic & kinematic,
//                                               const KinematicCommand & commandFrame)
//{
//  double wheelBase= kinematic.getWheelBase("wheelbase").get();
//  return forwardKinematic1FSA2FWD(emitterName,kinematic,toOneAxleSteeringCommand(commandFrame,wheelBase));
//}

//-----------------------------------------------------------------------------
void forwardKinematic(const OneAxleSteeringKinematic::Parameters &parameters,
                      const OneAxleSteeringCommand & commandFrame,
                      OdometryFrame1FAS2RWD & odometryCommandFrame)
{
  const double & wheelTrack = parameters.rearWheelTrack + 2*parameters.rearHubCarrierOffset;
  const double & wheelBase= parameters.frontWheelBase + parameters.rearWheelBase;
  const double & linearSpeed = commandFrame.longitudinalSpeed;
  const double & steeringAngle = commandFrame.steeringAngle;

  double instantaneousCurvature = std::tan(steeringAngle)/wheelBase;
  double rearLeftWheelSpeed  = SkidSteeringKinematic::computeLeftWheelSpeed(linearSpeed,instantaneousCurvature*linearSpeed,wheelTrack);
  double rearRightWheelSpeed =  SkidSteeringKinematic::computeRightWheelSpeed(linearSpeed,instantaneousCurvature*linearSpeed,wheelTrack);

  odometryCommandFrame.frontAxleSteeringAngle = steeringAngle;
  odometryCommandFrame.rearLeftWheelSpeed=rearLeftWheelSpeed;
  odometryCommandFrame.rearRightWheelSpeed=rearRightWheelSpeed;
}

////-----------------------------------------------------------------------------
//OdometryFrame1FAS2RWD forwardKinematic1FAS2RWD(const std::string &emitterName,
//                                               const OneAxleSteeringKinematic & kinematic,
//                                               const KinematicCommand & commandFrame)
//{
//  double wheelBase= kinematic.getWheelBase("wheelbase").get();
//  return forwardKinematic1FAS2RWD(emitterName,kinematic,toOneAxleSteeringCommand(commandFrame,wheelBase));
//}

}

