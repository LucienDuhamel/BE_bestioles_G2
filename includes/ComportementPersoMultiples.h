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
    std::vector<Comportement*> comportementsDisponibles;


    ComportementPersoMultiples()= delete;
    ComportementPersoMultiples(std::vector<Comportement*> listeComportements);
    ComportementPersoMultiples(const ComportementPersoMultiples&) = delete;
    ComportementPersoMultiples& operator=(const ComportementPersoMultiples&) = delete;

    static ComportementPersoMultiples* singletonPersoMultiples;

public:

    ~ComportementPersoMultiples();
    static ComportementPersoMultiples* getInstance(std::vector<Comportement*> listeComportements) ;
    static ComportementPersoMultiples* getInstance() ;

    T * couleur;
    T * getCouleur()  const override;
    std::string getNom() const override { return "PersoMultiples"; }
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const override;

};


#endif
