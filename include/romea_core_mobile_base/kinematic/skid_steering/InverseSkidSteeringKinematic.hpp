#ifndef romea_InverseSkidSteeringKinematic_hpp
#define romea_InverseSkidSteeringKinematic_hpp

//romea
#include "SkidSteeringKinematic.hpp"
#include "SkidSteeringMeasure.hpp"
#include "romea_core_mobile_base/odometry/OdometryFrame2TD.hpp"
#include "romea_core_mobile_base/odometry/OdometryFrame2WD.hpp"
#include "romea_core_mobile_base/odometry/OdometryFrame4WD.hpp"

namespace romea
{

void inverseKinematic(const SkidSteeringKinematic::Parameters & parameters,
                      const OdometryFrame2TD & odometryFrame,
                      SkidSteeringMeasure & skidSteeringMeasure);

void inverseKinematic(const SkidSteeringKinematic::Parameters & parameters,
                      const OdometryFrame2WD & odometryFrame,
                      SkidSteeringMeasure & skidSteeringMeasure);

void inverseKinematic(const SkidSteeringKinematic::Parameters & parameters,
                      const OdometryFrame4WD & odometryFrame,
                      SkidSteeringMeasure & skidSteeringMeasure);


}//end romea

#endif
