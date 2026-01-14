#ifndef RVSPHERICALCAMERA_H
#define RVSPHERICALCAMERA_H

#include "rvstereocamera.h"

class RVSphericalCamera : public RVStereoCamera
{
public:
    RVSphericalCamera();

    float getPhi() const;
    void setPhi(float newPhi);

    float getTheta() const;
    void setTheta(float newTheta);

    float getRho() const;
    void setRho(float newRho);

protected:
    float phi;
    float theta;
    float rho;

private:
    void updateposition();
};

#endif // RVSPHERICALCAMERA_H
