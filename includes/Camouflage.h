#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "IAccessoire.h"

class Camouflage : public IAccessoire
{

private: 
    static double camoMin;
    static double camoMax;
private:
    double camouflage;
public:
    Camouflage();
    ~Camouflage() = default;

    void draw(UImg& support, Bestiole* b) override;
    void setCamouflage(Bestiole* b);
    Camouflage* clone() const override;
    void initFromConfig();
};

#endif
