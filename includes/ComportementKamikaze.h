#ifndef _ComportementKamikaze_
#define _ComportementKamikaze_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <string>

class ComportementKamikaze : public Comportement
{
private: 
    // Configuration et Singleton 
    static ComportementKamikaze* singletonKamikaze;
    static T COULEUR_CFG[3];
    static bool configInitialized;

private:
    // Implémentation d'un Singleton
    ComportementKamikaze() {}
    ComportementKamikaze(const ComportementKamikaze&) = delete;
    ComportementKamikaze& operator=(const ComportementKamikaze&) = delete;
    
private:
    void initFromConfig();

public:
    static ComportementKamikaze* getInstance();
    Comportement* clone() const override;
    
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles ) override;

    T * getCouleur() const override;
    std::string getName() const override { return "Comportement Kamikaze"; }
    
};

#endif