#ifndef _ComportementPersoMultiples_
#define _ComportementPersoMultiples_

#include "config.h"
#include "Bestiole.h"
#include "Comportement.h"

#include <iostream>
#include <vector>
#include <string>

class ComportementPersoMultiples : public Comportement
{

private: 
    // Configuration
    static double     MAX_PROBA_CHANGEMENT_COMPORTEMENT;
    static bool       configInitialized;

private:
    std::vector<Comportement*> comportementsDisponibles;

    // État interne : Chaque bestiole a son propre index et une probabilité de changement de comportement
    int ComportementApparentIndex;
    double probaChangementComportement;

    void initFromConfig();

public:
    // Constructeur public (Pas de Singleton ici car le comportement a un état interne)
    ComportementPersoMultiples(std::vector<Comportement*> listeComportements);
    ~ComportementPersoMultiples();

    T * getCouleur() const override;

    // Méthode qui implémente le comportement avec changements aléatoires
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    Comportement* clone() const override;

    // Méthode pour obtenir le nom du comportement
    std::string getName() const override { return "Comportement Perso Multiples"; }
};


#endif