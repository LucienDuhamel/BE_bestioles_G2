#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "IAccessoire.h"

class Camouflage : public IAccessoire
{
private:
    double camouflage;
public:
    Camouflage();
    Camouflage(double camouflage);
    ~Camouflage() = default;

    void draw(UImg& support, Bestiole* b) override;
    void setCamouflage(Bestiole* b);
    Camouflage* clone() const override;
};

#endif
