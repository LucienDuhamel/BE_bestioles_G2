#ifndef _ComportementPeureux_
#define _ComportementPeureux_

#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementPeureux : public Comportement
{

private:
    ComportementPeureux() {}
    ComportementPeureux(const ComportementPeureux&) = delete;
    ComportementPeureux& operator=(const ComportementPeureux&) = delete;

    static ComportementPeureux* singletonPeureux;

public:
    static ComportementPeureux* getInstance();


    void bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const override;

};


#endif
