#ifndef VRSPHERE_H
#define VRSPHERE_H

/*!
  \file vrsphere.h
  \brief Déclaration de la classe VRSphere.
  \author  Leo Donati
  \date    01/02/2022
  \version 2

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Utilise VRsurface avec l'équation paramétrée utilisant les coordonnées sphériques
*/

#include "vrsurface.h"

class VRSphere : public VRSurface
{
public:
    VRSphere(double radius = 1.0);

    double getRadius() const;
    void setRadius(double newRadius);

protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    double radius;
};

#endif // VRSPHERE_H
