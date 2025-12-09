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
    // Variables statiques pour la configuration
    static ComportementKamikaze* singletonKamikaze;
    static T couleur_cfg[3];
    static bool configInitialized;

private:
    ComportementKamikaze() {}
    ComportementKamikaze(const ComportementKamikaze&) = delete;
    ComportementKamikaze& operator=(const ComportementKamikaze&) = delete;
    
    // Chargement de la config
    void initFromConfig();

public:
    static ComportementKamikaze* getInstance();
    Comportement* clone() const override;
    T * getCouleur() const override;
    
    // Méthode qui implémente le comportement kamikaze
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles ) override;

    // Méthode pour obtenir le nom du comportement
    std::string getName() const override { return "Comportement Kamikaze"; }
    
};

#endif