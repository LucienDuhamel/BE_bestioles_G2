#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "ICapteur.h"
#include <vector>

class Bestiole;

class Oreilles : public ICapteur
{
private:
    double distanceVisionOreilles;
    double pourcentageDetectionOreilles;
public:
    Oreilles();
    ~Oreilles() = default;

    void draw(UImg& support, Bestiole* b) override;
    std::vector<Bestiole*> detecter( std::vector<Bestiole*> listeBestioles, Bestiole* b ) override;
    Oreilles* clone() const override;
};

#endif
