#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_

#include "IAccessoire.h"

class Bestiole;

class Nageoires : public IAccessoire

{
private : 
   static double vitesseMax;
      static bool configInitialized;
private :
   double CoeffVitesseNageoires;

public:
    Nageoires();
    ~Nageoires() = default;

    void draw(UImg& support, Bestiole* b) override;
    void setParameters(Bestiole* b)  const override;
    void setVitesseNageoires(Bestiole* b) const;
    Nageoires* clone() const override;
    void initFromConfig();
};

#endif
