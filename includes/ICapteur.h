#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

#include "UImg.h"
#include "EspeceBestiole.h"
#include <vector>
class Bestiole;

class ICapteur
{
public:
    virtual ~ICapteur() = default;

    virtual void draw(UImg& support, Bestiole* b) = 0;
    virtual std::vector<EspeceBestiole*> detecter( std::vector<EspeceBestiole*> listeBestioles, Bestiole* b ) = 0;
    virtual ICapteur* clone() const = 0;
};

#endif