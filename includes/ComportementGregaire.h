#ifndef _COMPORTEMENT_GREGAIRE_H_
#define _COMPORTEMENT_GREGAIRE_H_

#include "ComportementBestiole.h"

#include <iostream>

using namespace std;

class Bestiole;

// Classe pour le comportement grégaire des bestioles
class ComportementGregaire : public ComportementBestiole {

private :
    string getNameComportement() const override final;
    void bouge(Bestiole& bestiole, std::vector< unique_ptr<Bestiole> > listeBestioles) const override final;

public :
    ComportementGregaire( void );
    ~ComportementGregaire( void );

};


#endif