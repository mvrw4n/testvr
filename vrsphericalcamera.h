#ifndef VRSPHERICALCAMERA_H
#define VRSPHERICALCAMERA_H

#include "vrcamera.h"

class VRSphericalCamera : public VRCamera
{
public:
    VRSphericalCamera();

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

#endif // VRSPHERICALCAMERA_H
