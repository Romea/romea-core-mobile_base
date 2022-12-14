#ifndef ROMEA_CORE_MOBILE_BASE_KINEMATIC_AXLE_STEERING_INVERSETWOAXLESTEERINGKINEMATIC_HPP_
#define ROMEA_CORE_MOBILE_BASE_KINEMATIC_AXLE_STEERING_INVERSETWOAXLESTEERINGKINEMATIC_HPP_

// romea
#include "romea_core_mobile_base/kinematic/axle_steering/TwoAxleSteeringMeasure.hpp"
#include "romea_core_mobile_base/kinematic/axle_steering/TwoAxleSteeringKinematic.hpp"
#include "romea_core_mobile_base/odometry/OdometryFrame2AS4WD.hpp"

namespace romea {

void inverseKinematic(const TwoAxleSteeringKinematic::Parameters &parameters,
                      const OdometryFrame2AS4WD & odometryFrame,
                      TwoAxleSteeringMeasure & twoAxleSteeringMeasure);


}  // namespace romea

#endif  // ROMEA_CORE_MOBILE_BASE_KINEMATIC_AXLE_STEERING_INVERSETWOAXLESTEERINGKINEMATIC_HPP_
