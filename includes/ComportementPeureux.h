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
    static T couleur_cfg[3];

    // Paramètres statiques récupérés depuis le fichier de configuration
    static int BESTIOLE_SCARED_NUMBER;    // Nombre de bestioles détectées pour être effrayé
    static int REMAINING_SCARED_STEPS;    // Nombre d'étapes restantes à être effrayé
    static double SPEED_COEF;             // Coefficient de vitesse quand effrayé
    static bool configInitialized;

private : 
    // État propre à CHAQUE instance
    // Pas de "mutable" car reagit n'est pas const
    bool isScared = false;
    int nbStep = 0;

private:
    void initFromConfig();

public:
    // Constructeur public (Pas de getInstance car chaque bestiole a son propre objet)
    ComportementPeureux();
    ~ComportementPeureux();

    T * getCouleur() const override;

    // Méthode qui implémente le comportement peureux   
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    Comportement* clone() const override;

    // Méthode qui retourne le nom du comportement
    std::string getName() const override { return "Comportement Peureux"; }

};

#endif