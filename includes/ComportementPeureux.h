#ifndef _ComportementPeureux_
#define _ComportementPeureux_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementPeureux : public Comportement
{
private : 
    // Couleur statique récupérée depuis le fichier de configuration
    static T couleur_cfg[3];

    // Paramètres statiques récupérés depuis le fichier de configuration
    static int BESTIOLE_SCARED_NUMBER; // Nombre de bestioles détectées pour être effrayé
    static int REMAINING_SCARED_STEPS; // Nombre d'étapes restantes à être effrayé
    static double SPEED_COEF;             // Coefficient de vitesse quand effrayé

    // États modifiés lors de l'exécution (valeurs par défaut)
    mutable bool isScared = false;
    mutable int nbStep = 0;
    mutable double vIni = 0.0;

private:
    ComportementPeureux() {}
    ComportementPeureux(const ComportementPeureux&) = delete;
    ComportementPeureux& operator=(const ComportementPeureux&) = delete;

    void initFromConfig();
    T * couleur;
    static ComportementPeureux* singletonPeureux;

public:
    static ComportementPeureux* getInstance();

    T * getCouleur()  const override;
    std::string getNom() const override { return "Peureux"; }
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const override;

};


#endif
