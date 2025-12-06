#ifndef _ComportementPrevoyant_
#define _ComportementPrevoyant_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"
#include "utils.h"

#include <iostream>
#include <vector>



class ComportementPrevoyant : public Comportement
{
private:
    static ComportementPrevoyant* singletonPrevoyant;
    static T couleur_cfg[3];
    static double T_PREDICT;
    static double DIST_MIN_COLLISION;
    static bool configInitialized;

private:
    ComportementPrevoyant() {}
    ComportementPrevoyant(const ComportementPrevoyant&) = delete;
    ComportementPrevoyant& operator=(const ComportementPrevoyant&) = delete;

    void initFromConfig();

public:
    static ComportementPrevoyant* getInstance();
    Comportement* clone() const override;
    T * getCouleur()  const override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;

};


#endif
