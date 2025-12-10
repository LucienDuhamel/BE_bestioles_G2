#ifndef _ComportementPeureux_
#define _ComportementPeureux_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>
#include <string>

class ComportementPeureux : public Comportement
{

private :
    // Paramètres statiques récupérés depuis le fichier de configuration
    static T COULEUR_CFG[3];
    static int BESTIOLE_SCARED_NUMBER;    // Nombre de bestioles détectées pour être effrayé
    static int REMAINING_SCARED_STEPS;    // Nombre d'étapes restantes à être effrayé
    static double SPEED_COEF;             // Coefficient de vitesse quand effrayé
    static bool configInitialized;

private : 
    // État propre à chaque instance
    bool isScared = false;
    int nbStep = 0;

private:
    void initFromConfig();

public:
    // Constructeur public (pas de getInstance car chaque bestiole a son propre comportement peureux)
    ComportementPeureux();
    ~ComportementPeureux();
    
    Comportement* clone() const override;

    // Méthode qui implémente le comportement peureux   
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;

    T * getCouleur() const override;
    std::string getName() const override { return "Comportement Peureux"; }

};

#endif