#ifndef _ComportementPersoMultiples_
#define _ComportementPersoMultiples_

#include "config.h"
#include "Bestiole.h"
#include "Comportement.h"

#include <iostream>
#include <vector>



class ComportementPersoMultiples : public Comportement
{

private: 
    static double     MAX_PROBA_CHANGEMENT_COMPORTEMENT;
    static bool configInitialized;

private:
    std::vector<Comportement*> comportementsDisponibles;

    int ComportementApparentIndex;
    // Pour les bestioles a comportements multiples
    double probaChangementComportement;

    void initFromConfig();



    public:
    ComportementPersoMultiples(std::vector<Comportement*> listeComportements);
    ~ComportementPersoMultiples();
    T * getCouleur()  const override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    Comportement* clone() const override;
};


#endif
