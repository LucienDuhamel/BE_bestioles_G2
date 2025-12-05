#ifndef _IACCESSOIRE_H_
#define _IACCESSOIRE_H_
#include "UImg.h"
#include <vector>

class Bestiole;

class IAccessoire
{
public:
    virtual ~IAccessoire() = default;

    virtual void draw(UImg& support, Bestiole* b) = 0;
    virtual void setParameters(Bestiole* b)  const= 0;
    virtual IAccessoire* clone() const = 0;
};

#endif
