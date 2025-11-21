#ifndef _COMPORTEMENT_BESTIOLE_H_
#define _COMPORTEMENT_BESTIOLE_H_

#include <iostream>

using namespace std;

class Bestiole;

// classe asbtraite pour le comportement des bestioles
class ComportementBestiole
{

public :
    ComportementBestiole( void );
    ~ComportementBestiole( void );
    virtual string getNameComportement() const = 0;
    virtual void bouge(Bestiole& bestiole, std::vector< unique_ptr<Bestiole> > listeBestioles) const = 0;

};


#endif
