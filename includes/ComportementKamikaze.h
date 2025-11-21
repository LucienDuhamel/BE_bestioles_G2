#ifndef _COMPORTEMENT_KAMIKAZE_H_
#define _COMPORTEMENT_KAMIKAZE_H_

#include "Milieu.h"
#include "Bestiole.h"

#include <iostream>

using namespace std;

class Bestiole;

// Classe pour le comportement grégaire des bestioles
class ComportementKamikaze : public ComportementBestiole {

private :
    void bouge(Bestiole& bestiole, std::vector< unique_ptr<Bestiole> > listeBestioles) const override final;;
    string getNameComportement() const override final;

public :
    ComportementKamikaze( void );
    ~ComportementKamikaze( void );

};


#endif