#ifndef VRDICE_H
#define VRDICE_H

#include "vrbody.h"

class VRDice : public VRBody
{
public:
    VRDice();

public:
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    void initializeBuffer() override;
    void initializeVAO() override;
};

#endif // VRDICE_H
