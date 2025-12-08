#ifndef _ComportementPeureux_
#define _ComportementPeureux_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>
#include <string> // Nécessaire pour getName()

class ComportementPeureux : public Comportement
{

private :
    // Couleur statique récupérée depuis le fichier de configuration (Main)
    static T couleur_cfg[3];

    // Paramètres statiques récupérés depuis le fichier de configuration (Main)
    static int BESTIOLE_SCARED_NUMBER;    // Nombre de bestioles détectées pour être effrayé
    static int REMAINING_SCARED_STEPS;    // Nombre d'étapes restantes à être effrayé
    static double SPEED_COEF;             // Coefficient de vitesse quand effrayé
    static bool configInitialized;

private : 
    // État propre à CHAQUE instance (Main)
    // Pas de "mutable" car reagit n'est pas const
    bool isScared = false;
    int nbStep = 0;

private:
    void initFromConfig();

public:
    // Constructeur public (Pas de getInstance car chaque bestiole a son propre objet)
    ComportementPeureux();
    ~ComportementPeureux();

    // Méthodes de l'architecture Main
    T * getCouleur() const override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    Comportement* clone() const override;

    // Votre ajout pour l'analyse
    std::string getName() const override { return "Comportement Peureux"; }

};

#endif