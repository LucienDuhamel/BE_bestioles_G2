#include "Bestiole.h"
#include "ComportementGregaire.h"
#include "utils.h"

#include <iostream>
#include <vector>

ComportementGregaire* ComportementGregaire::singletonGregaire = nullptr;
T ComportementGregaire::couleur_cfg[3] = {0, 0, 0};

ComportementGregaire*  ComportementGregaire::getInstance()  
{
    if (singletonGregaire == nullptr){
        singletonGregaire = new ComportementGregaire();
        
        if(couleur_cfg[0]==0 && couleur_cfg[1]==0 && couleur_cfg[2]==0){
            singletonGregaire->initFromConfig();
        }

    }

    return  singletonGregaire;
}

Comportement* ComportementGregaire::clone() const {
    // Just return the singleton
    return getInstance();
}


// Initialisation des parametres statiques depuis le fichier de config (valeurs par defaut si absentes)
void ComportementGregaire::initFromConfig() {
    // par défaut : orange
    couleur_cfg[0] = Config::getInstance().getInt("GREG_COULEUR_R", 255);
    couleur_cfg[1] = Config::getInstance().getDouble("GREG_COULEUR_G", 128);
    couleur_cfg[2] = Config::getInstance().getDouble("GREG_COULEUR_B", 0);
}

T * ComportementGregaire::getCouleur() const {
    return couleur_cfg;
}
void ComportementGregaire::reagit( Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles)
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    if (bestiolesVisibles.empty()) return;   // éviter division par zéro

    double mOrientation = 0.0;

    for (EspeceBestiole* b : bestiolesVisibles) {
        mOrientation += b->getOrientation();
    }

    mOrientation /= bestiolesVisibles.size();
    bestiole.setOrientation(mOrientation);
}
