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
    void setParameters(Bestiole* b) const override;
    void setVitesseCarapace(Bestiole* b) const;
    void setResistanceCarapace(Bestiole* b) const;
    Carapace* clone() const override;
    void initFromConfig();
};

#endif
