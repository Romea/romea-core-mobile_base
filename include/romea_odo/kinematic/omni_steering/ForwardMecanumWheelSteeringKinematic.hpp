#ifndef romea_ForwardMecanumWheelSteeringKinematic_hpp
#define romea_ForwardMecanumWheelSteeringKinematic_hpp

//romea
#include "OmniSteeringCommand.hpp"
#include "MecanumWheelSteeringKinematic.hpp"
#include "romea_odo/odometry/OdometryFrame2WD.hpp"
#include "romea_odo/odometry/OdometryFrame4WD.hpp"

namespace romea
{

void forwardKinematic(const MecanumWheelSteeringKinematic::Parameters & parameters,
                      const OmniSteeringCommand & commandFrame,
                      OdometryFrame4WD & odometryFrame);


}//end romea

#endif
