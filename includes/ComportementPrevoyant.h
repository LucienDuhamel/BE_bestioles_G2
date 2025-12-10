#ifndef _ComportementPrevoyant_
#define _ComportementPrevoyant_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <string> 

class ComportementPrevoyant : public Comportement
{
private:
    // Configuration et Singleton 
    static ComportementPrevoyant* singletonPrevoyant;
    static T COULEUR_CFG[3];
    static bool configInitialized;

private:
    // Implémentation d'un Singleton
    ComportementPrevoyant() {}
    ComportementPrevoyant(const ComportementPrevoyant&) = delete;
    ComportementPrevoyant& operator=(const ComportementPrevoyant&) = delete;

private:
    void initFromConfig();

public:
    static ComportementPrevoyant* getInstance();
    Comportement* clone() const override;
    
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;

    T * getCouleur() const override;
    std::string getName() const override { return "Comportement Prevoyant"; }

};


#endif