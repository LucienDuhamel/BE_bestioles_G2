#ifndef _ComportementKamikaze_
#define _ComportementKamikaze_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <string> // Nécessaire pour getName()

class ComportementKamikaze : public Comportement
{

private: 
    // Variables statiques pour la configuration (Architecture Main)
    static ComportementKamikaze* singletonKamikaze;
    static T couleur_cfg[3];
    static bool configInitialized;

private:
    ComportementKamikaze() {}
    ComportementKamikaze(const ComportementKamikaze&) = delete;
    ComportementKamikaze& operator=(const ComportementKamikaze&) = delete;
    
    // Chargement de la config (Main)
    void initFromConfig();

public:
    static ComportementKamikaze* getInstance();

    // Méthodes requises par l'architecture Main
    Comportement* clone() const override;
    T * getCouleur() const override;
    
    // Signature non-const (compatible avec la classe mère du Main)
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles ) override;

    // Votre ajout pour l'analyse
    std::string getName() const override { return "Comportement Kamikaze"; }
    
};

#endif