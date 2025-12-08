#ifndef _ComportementPrevoyant_
#define _ComportementPrevoyant_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <string> // Nécessaire pour getName()

class ComportementPrevoyant : public Comportement
{
private:
    // Configuration et Singleton (Architecture Main)
    static ComportementPrevoyant* singletonPrevoyant;
    static T couleur_cfg[3];
    static double T_PREDICT;
    static double DIST_MIN_COLLISION;
    static bool configInitialized;

private:
    ComportementPrevoyant() {}
    ComportementPrevoyant(const ComportementPrevoyant&) = delete;
    ComportementPrevoyant& operator=(const ComportementPrevoyant&) = delete;

    void initFromConfig();

public:
    static ComportementPrevoyant* getInstance();

    // Méthodes de l'architecture Main
    Comportement* clone() const override;
    T * getCouleur() const override;
    
    // Signature non-const pour compatibilité
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;

    // Votre ajout pour l'analyse
    std::string getName() const override { return "Comportement Prevoyant"; }

};


#endif