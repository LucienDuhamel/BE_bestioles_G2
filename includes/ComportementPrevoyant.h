#ifndef _ComportementPrevoyant_
#define _ComportementPrevoyant_

#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementPrevoyant : public Comportement
{
private:
    static constexpr double T_PREDICT = 15.0;
    static constexpr double DIST_MIN_COLLISION = 30.0;
    static constexpr double AVOID_STRENGTH = 1.5;

private:
    ComportementPrevoyant() {}
    ComportementPrevoyant(const ComportementPrevoyant&) = delete;
    ComportementPrevoyant& operator=(const ComportementPrevoyant&) = delete;

    T * couleur;
    static ComportementPrevoyant* singletonPrevoyant;

public:
    static ComportementPrevoyant* getInstance();

    T * getCouleur()  const override;

    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const override;

};


#endif
