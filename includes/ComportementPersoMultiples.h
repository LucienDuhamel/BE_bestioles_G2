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
    // Paramètres statiques récupérés depuis le fichier de configuration
    static double     MAX_PROBA_CHANGEMENT_COMPORTEMENT;
    static bool       configInitialized;

private:
    // État propre à chaque instance
    std::vector<Comportement*> comportementsDisponibles;
    int comportementApparentIndex;
    double probaChangementComportement;

private:  
    void initFromConfig();

public:
    // Constructeur public (Pas de getInstance car chaque bestiole a son propre comportement perso multiples)
    ComportementPersoMultiples(std::vector<Comportement*> listeComportements);
    ~ComportementPersoMultiples();

    Comportement* clone() const override;

    // Méthode qui implémente le comportement à personnalités multiples
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;

    T * getCouleur() const override;
    std::string getName() const override { return "Comportement Perso Multiples"; }
};


#endif