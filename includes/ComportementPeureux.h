#ifndef _COMPORTEMENT_PEUREUX_H_
#define _COMPORTEMENT_PEUREUX_H_

#include "Milieu.h"
#include "Bestiole.h"

#include <iostream>

using namespace std;

class Bestiole;

// Classe pour le comportement grégaire des bestioles
class ComportementPeureux : public ComportementBestiole {

private :
    static const int BESTIOLE_SCARED_NUMBER = 3;
    static const int REMAINING_SCARED_STEPS = 2;
    static const int SPEED_COEF = 5;
    void bouge(Bestiole& bestiole, std::vector< unique_ptr<Bestiole> > listeBestioles) const override final;
    string getNameComportement() const override final;
public :
    ComportementPeureux( void );
    ~ComportementPeureux( void );

};


#endif