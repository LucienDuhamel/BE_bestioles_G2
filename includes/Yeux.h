#ifndef _YEUX_H_
#define _YEUX_H_

#include "ICapteur.h"
#include <vector>

class Bestiole;

class Yeux : public ICapteur
{
private:
    double angleVisionYeux;
    double distanceVisionYeux;
    double pourcentageDetectionYeux;

public:
    Yeux();
    ~Yeux() = default;

    void draw(UImg& support, Bestiole* b) override;
    std::vector<Bestiole*> detecter( std::vector<Bestiole*> listeBestioles, Bestiole* b ) override;
    Yeux* clone() const override;
};

#endif