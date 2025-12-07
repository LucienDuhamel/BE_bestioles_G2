#ifndef _ComportementPersoMultiples_
#define _ComportementPersoMultiples_


#include "Bestiole.h"
#include "Comportement.h"

#include <iostream>
#include <vector>



class ComportementPersoMultiples : public Comportement
{
private:
   std::vector<Comportement*> listeComportements;


    ComportementPersoMultiples() {}
    ComportementPersoMultiples(const std::vector<Comportement*>& comportementsDisponibles);
    ComportementPersoMultiples(const ComportementPersoMultiples&) = delete;
    ComportementPersoMultiples& operator=(const ComportementPersoMultiples&) = delete;

    T* couleur;

    static ComportementPersoMultiples* singletonPersoMultiples;

public:

    ~ComportementPersoMultiples();
    static ComportementPersoMultiples* getInstance(const std::vector<Comportement*>& listeComportements);
    static ComportementPersoMultiples* getInstance();

    T* getCouleur() const override;

    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&   listeBestioles ) const override;

    std::string getName() const override { return "Comportement Perso Multiples"; }

};


#endif
