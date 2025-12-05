#ifndef _ComportementPrevoyant_
#define _ComportementPrevoyant_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementPrevoyant : public Comportement
{
private:
    static T couleur_cfg[3];
    static double T_PREDICT;
    static double DIST_MIN_COLLISION;

private:
    ComportementPrevoyant() {}
    ComportementPrevoyant(const ComportementPrevoyant&) = delete;
    ComportementPrevoyant& operator=(const ComportementPrevoyant&) = delete;

    void initFromConfig();
    static ComportementPrevoyant* singletonPrevoyant;

public:
    static ComportementPrevoyant* getInstance();
    Comportement* clone() const override;
    T * getCouleur()  const override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;

};


#endif
