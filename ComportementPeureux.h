#ifndef _ComportementPeureux_
#define _ComportementPeureux_

#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementPeureux : public Comportement
{

private : 
    static const int BESTIOLE_SCARED_NUMBER = 3; // Nombre de bestioles détectées pour être effrayé
    static const int REMAINING_SCARED_STEPS = 2; // Nombre d'étapes restantes à être effrayé
    static const int SPEED_COEF = 5;             // Coefficient de vitesse quand effrayé

    // États modifiés lors de l'exécution (valeurs par défaut)
    mutable bool isScared = false;
    mutable int nbStep = 0;
    mutable double vIni = 0.0;

private:
    ComportementPeureux() {}
    ComportementPeureux(const ComportementPeureux&) = delete;
    ComportementPeureux& operator=(const ComportementPeureux&) = delete;

    static ComportementPeureux* singletonPeureux;

public:
    static ComportementPeureux* getInstance();


    void bouge(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const override;

};


#endif