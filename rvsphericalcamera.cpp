#include "rvsphericalcamera.h"
#include "QtMath"
#include <math.h>

RVSphericalCamera::RVSphericalCamera() : RVCamera()
{
    rho = 20;
    theta = 0;
    phi = (float)M_PI/4;

    target = QVector3D(0, 0, 0);

    updateposition();
}

float RVSphericalCamera::getPhi() const
{
    return phi;
}

void RVSphericalCamera::setPhi(float newPhi)
{
    if (newPhi > -M_PI/2 && newPhi < M_PI/2){
        phi = newPhi;
        updateposition();
    }
}

float RVSphericalCamera::getTheta() const
{
    return theta;
}

void RVSphericalCamera::setTheta(float newTheta)
{
    theta = newTheta;
    updateposition();
}

float RVSphericalCamera::getRho() const
{
    return rho;
}

void RVSphericalCamera::setRho(float newRho)
{
    if (newRho > 0){
        rho = newRho;
        updateposition();
    }
}

void RVSphericalCamera::updateposition()
{
    float pos_x = target.x() + rho*qCos(phi)*qCos(theta);
    float pos_y = target.y() + rho*qSin(phi);
    float pos_z = target.z() + rho*qCos(phi)*qSin(theta);
    setPosition(QVector3D(pos_x,pos_y,pos_z));
}
