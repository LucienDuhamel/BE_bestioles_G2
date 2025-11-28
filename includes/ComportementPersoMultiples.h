#ifndef _ComportementPersoMultiples_
#define _ComportementPersoMultiples_


#include "Bestiole.h"
#include "Comportement.h"

#include <iostream>
#include <vector>



class ComportementPersoMultiples : public Comportement
{

private:
    static constexpr double PROBA_CHANGEMENT_COMPORTEMENT = 0.010;
    std::vector<Comportement*> listeComportements;
    Comportement* comportementCourant;
    T * couleur;

public:

    ComportementPersoMultiples(const std::vector<Comportement*>& comportementsDisponibles);
    ~ComportementPersoMultiples();
    ComportementPersoMultiples(const ComportementPersoMultiples&);
    ComportementPersoMultiples& operator=(const ComportementPersoMultiples&) = delete;

    T * getCouleur()  const override;
    std::string getNom() const override { return "PersoMultiples"; }
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;

};


#endif
