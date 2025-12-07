#ifndef _ComportementPrevoyant_
#define _ComportementPrevoyant_

#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementPrevoyant : public Comportement
{

private:
    ComportementPrevoyant() {}
    ComportementPrevoyant(const ComportementPrevoyant&) = delete;
    ComportementPrevoyant& operator=(const ComportementPrevoyant&) = delete;

    static ComportementPrevoyant* singletonPrevoyant;

public:
    static ComportementPrevoyant* getInstance();


    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&   listeBestioles ) const override;

    std::string getName() const override { return "Comportement Prevoyant"; }

};


#endif
