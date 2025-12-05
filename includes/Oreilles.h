#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "ICapteur.h"
#include <vector>

class Bestiole;

class Oreilles : public ICapteur
{
private: 
    static double distMin;
    static double distMax;
    static double pourcMin;
    static double pourcMax;
private:
    double distanceVisionOreilles;
    double pourcentageDetectionOreilles;
public:
    Oreilles();
    ~Oreilles() = default;

    void draw(UImg& support, Bestiole* b) override;
    std::vector<EspeceBestiole*> detecter( std::vector<EspeceBestiole*> listeBestioles, Bestiole* b ) override;
    Oreilles* clone() const override;
    void initFromConfig();
};

#endif
