#ifndef ROMEA_CORE_MOBILE_BASE_ODOMETRY_ODOMETRYFRAME1FAS2FWD_HPP_ 
#define ROMEA_CORE_MOBILE_BASE_ODOMETRY_ODOMETRYFRAME1FAS2FWD_HPP_ 

// stl
#include <ostream>

namespace romea {

struct OdometryFrame1FAS2FWD
{
  double frontAxleSteeringAngle;
  double frontLeftWheelLinearSpeed;
  double frontRightWheelLinearSpeed;
};

std::ostream & operator<<(std::ostream &s, const OdometryFrame1FAS2FWD &frame);

} // namespace romea

#endif  // ROMEA_CORE_MOBILE_BASE_ODOMETRY_ODOMETRYFRAME1FAS2FWD_HPP_ 
