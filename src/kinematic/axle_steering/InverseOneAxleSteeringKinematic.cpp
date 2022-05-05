//romea
#include "romea_core_mobile_base/kinematic/axle_steering/InverseOneAxleSteeringKinematic.hpp"

namespace romea {


//-----------------------------------------------------------------------------
void inverseKinematic(const OneAxleSteeringKinematic::Parameters & parameters,
                      const OdometryFrame1FAS2FWD & odometryFrame,
                      OneAxleSteeringMeasure & oneAxleSteeringMeasure)
{

  const double &wheelSpeedVariance = parameters.wheelSpeedVariance;
  const double &steeringAngleVariance = parameters.steeringAngleVariance;

  const double halfWheelTrack = parameters.frontWheelTrack/2;
  const double wheelBase = parameters.frontWheelBase+parameters.rearWheelBase;
  const double hubCarrierOffset = parameters.rearHubCarrierOffset;

  const double & frontLeftWheelSpeed = odometryFrame.frontLeftWheelSpeed;
  const double & frontRightWheelSpeed = odometryFrame.frontRightWheelSpeed;
  const double & frontSteeringAngle = odometryFrame.frontAxleSteeringAngle;

  double tanFrontSteeringAngle = std::tan(frontSteeringAngle);
  double instantaneousCurvature =tanFrontSteeringAngle/wheelBase;
  double instantaneousCurvatureHalfTrack_ = instantaneousCurvature*halfWheelTrack;
  
  double alphaLeft = 1 - instantaneousCurvatureHalfTrack_;
  double alphaRight =1 + instantaneousCurvatureHalfTrack_;
  double squareTanFrontSteeringAngle = tanFrontSteeringAngle*tanFrontSteeringAngle;
  double betaLeft =  std::sqrt(alphaLeft*alphaLeft+squareTanFrontSteeringAngle);
  double betaRight = std::sqrt(alphaRight*alphaRight+squareTanFrontSteeringAngle);
  double gammaLeft = betaLeft - tanFrontSteeringAngle*hubCarrierOffset/wheelBase;
  double gammaRight = betaRight + tanFrontSteeringAngle*hubCarrierOffset/wheelBase;


  Eigen::Matrix3d covariance = Eigen::Matrix3d::Zero();
  covariance(0,0)=wheelSpeedVariance;
  covariance(1,1)=wheelSpeedVariance;
  covariance(2,2)=steeringAngleVariance;

  Eigen::MatrixXd J = Eigen::MatrixXd::Zero(2,3);
  J(0,0) = 0.5/gammaLeft;
  J(0,1) = 0.5/gammaRight;
  J(0,2) += (2*(alphaLeft*halfWheelTrack/wheelBase+tanFrontSteeringAngle)/betaLeft - hubCarrierOffset/wheelBase)/(gammaLeft*gammaLeft);
  J(0,2) += (2*(alphaRight*halfWheelTrack/wheelBase+tanFrontSteeringAngle)/betaRight - hubCarrierOffset/wheelBase)/(gammaRight*gammaRight);
  J(0,2) *= 0.5*(1+tanFrontSteeringAngle*tanFrontSteeringAngle);
  J(1,2) =1;
  
  oneAxleSteeringMeasure.steeringAngle= frontSteeringAngle;
  oneAxleSteeringMeasure.longitudinalSpeed = 0.5*(frontLeftWheelSpeed/gammaLeft +frontRightWheelSpeed/gammaRight);
  oneAxleSteeringMeasure.covariance =  J*covariance*J.transpose();
  
}

//-----------------------------------------------------------------------------
void inverseKinematic(const OneAxleSteeringKinematic::Parameters & parameters,
                      const OdometryFrame1FAS2RWD & odometryFrame,
                      OneAxleSteeringMeasure & oneAxleSteeringMeasure)
{
  
  const double &wheelSpeedVariance = parameters.wheelSpeedVariance;
  const double &steeringAngleVariance = parameters.steeringAngleVariance;

  const double & steeringAngle = odometryFrame.frontAxleSteeringAngle;
  const double & rearLeftWheelSpeed = odometryFrame.rearLeftWheelSpeed;
  const double & rearRightWheelSpeed = odometryFrame.rearRightWheelSpeed;
  
  oneAxleSteeringMeasure.steeringAngle= steeringAngle;
  oneAxleSteeringMeasure.longitudinalSpeed = 0.5*(rearLeftWheelSpeed+rearRightWheelSpeed);
  oneAxleSteeringMeasure.covariance(0,0)=  0.5*wheelSpeedVariance;
  oneAxleSteeringMeasure.covariance(1,1)=  steeringAngleVariance;
  
}

}

