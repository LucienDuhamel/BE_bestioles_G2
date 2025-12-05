#ifndef _YEUX_H_
#define _YEUX_H_

#include "ICapteur.h"
#include <vector>

class Bestiole;

class Yeux : public ICapteur
{
private: 
    static double angleMin;
    static double angleMax;
    static double distMin;
    static double distMax;
    static double pourcMin;
    static double pourcMax;
    
private:
    double angleVisionYeux;
    double distanceVisionYeux;
    double pourcentageDetectionYeux;

public:
    Yeux();
    ~Yeux() = default;

    void draw(UImg& support, Bestiole* b) override;
    std::vector<EspeceBestiole*> detecter( std::vector<EspeceBestiole*> listeBestioles, Bestiole* b ) override;
    Yeux* clone() const override;
    void initFromConfig();
};

#endif