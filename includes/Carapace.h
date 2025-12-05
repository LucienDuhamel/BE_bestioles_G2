#ifndef _CARAPACE_H_
#define _CARAPACE_H_

#include "IAccessoire.h"

class Carapace : public IAccessoire
{
private :
    static double vitesseMax;
    static double resistMax;
    double CoeffVitesseCarapace;
    double CoeffResistanceCarapace;
public:
    Carapace();
    ~Carapace() = default;

    void draw(UImg& support, Bestiole* b) override;
    void setVitesseCarapace(Bestiole* b);
    void setResistanceCarapace(Bestiole* b);
    Carapace* clone() const override;
    void initFromConfig();
};

#endif
