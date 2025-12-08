#ifndef _ComportementPersoMultiples_
#define _ComportementPersoMultiples_

#include "config.h"
#include "Bestiole.h"
#include "Comportement.h"

#include <iostream>
#include <vector>
#include <string> // Nécessaire pour getName()

class ComportementPersoMultiples : public Comportement
{

private: 
    // Configuration (Main)
    static double     MAX_PROBA_CHANGEMENT_COMPORTEMENT;
    static bool       configInitialized;

private:
    std::vector<Comportement*> comportementsDisponibles;

    // État interne (Main) : Chaque bestiole a son propre index
    int ComportementApparentIndex;
    double probaChangementComportement;

    void initFromConfig();

public:
    // Constructeur public (Pas de Singleton ici car le comportement a un état interne)
    ComportementPersoMultiples(std::vector<Comportement*> listeComportements);
    ~ComportementPersoMultiples();

    // Méthodes de l'architecture Main
    T * getCouleur() const override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    Comportement* clone() const override;

    // Votre ajout pour l'analyse
    std::string getName() const override { return "Comportement Perso Multiples"; }
};


#endif