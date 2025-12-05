#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_

#include "IAccessoire.h"

class Bestiole;

class Nageoires : public IAccessoire

{
private :
   double CoeffVitesseNageoires;

public:
    Nageoires();
    ~Nageoires() = default;

    void draw(UImg& support, Bestiole* b) override;
    void setVitesseNageoires(Bestiole* b);
    Nageoires* clone() const override;
};

#endif
