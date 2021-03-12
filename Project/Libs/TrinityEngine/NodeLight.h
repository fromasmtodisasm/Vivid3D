#pragma once
#include "NodeBase.h"
class NodeLight :
    public NodeBase
{
public:
    NodeLight();
    Vect3 GetDiffuse();
    Vect3 GetSpecular();
    float GetRange();
    float GetShininess();
    void SetDiffuse(Vect3 diff);
    void SetSpecular(Vect3 spec);
    void SetRange(float range);
    void SetShininess(float shine);
private:
    Vect3 Diffuse;
    Vect3 Specular;
    float Range;
    float Shininess;
};

