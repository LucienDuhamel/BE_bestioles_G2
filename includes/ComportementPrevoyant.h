#ifndef _COMPORTEMENT_PREVOYANT_H_
#define _COMPORTEMENT_PREVOYANT_H_

#include "Milieu.h"
#include "Bestiole.h"

#include <iostream>

using namespace std;

class Bestiole;

// Classe pour le comportement grégaire des bestioles
class ComportementPrevoyant : public ComportementBestiole {

private :
    void bouge(Bestiole& b, std::vector< unique_ptr<Bestiole> > listeBestioles) const override final;
    string getNameComportement() const override final;

public :
    ComportementPrevoyant( void );
    ~ComportementPrevoyant( void );

};


#endif