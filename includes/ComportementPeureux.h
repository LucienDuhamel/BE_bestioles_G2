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
    static int BESTIOLE_SCARED_NUMBER;    // Nombre de bestioles détectées pour être effrayé
    static int REMAINING_SCARED_STEPS;    // Nombre d'étapes restantes à être effrayé
    static double SPEED_COEF;             // Coefficient de vitesse quand effrayé
    static bool configInitialized;

private : 
    bool isScared = false;
    int nbStep = 0;

private:
    void initFromConfig();

public:
    ComportementPeureux();
    ~ComportementPeureux();
    T * getCouleur()  const override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    Comportement* clone() const override;

};


#endif
