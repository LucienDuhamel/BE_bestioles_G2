#include "Bestiole.h"
#include "ComportementGregaire.h"
#include "utils.h"

#include <iostream>
#include <vector>

ComportementGregaire* ComportementGregaire::singletonGregaire = nullptr;
T ComportementGregaire::COULEUR_CFG[3] = {0, 0, 0};
bool ComportementGregaire::configInitialized = false;

ComportementGregaire* ComportementGregaire::getInstance()  
{
    if (singletonGregaire == nullptr){
        singletonGregaire = new ComportementGregaire();
        
        if(configInitialized == false) {
            singletonGregaire->initFromConfig();
            configInitialized = true;
        }

    }

    return  singletonGregaire;
}

Comportement* ComportementGregaire::clone() const {
    return getInstance();
}


/**
 * @brief Comportement grégaire : oriente la bestiole vers la direction moyenne des especesBestioles détectées.
 * 
 * La bestiole calcule l'orientation moyenne de tous les especesBestioles visibles
 * et adopte cette direction pour rester cohérente avec le groupe.
 * 
 * @param bestiole La bestiole qui adopte ce comportement
 * @param listeBestioles Liste de toutes les bestioles du milieu
 * 
 * @details
 * - Détecte les bestioles visibles selon les capteurs de la bestiole
 * - Calcule la moyenne des orientations des visibles
 * - Oriente la bestiole vers cette direction moyenne
 */
void ComportementGregaire::reagit( Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles)
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    if (bestiolesVisibles.empty()) return;

    double mOrientation = 0.0;

    for (EspeceBestiole* b : bestiolesVisibles) {
        mOrientation += b->getOrientation();
    }

    mOrientation /= bestiolesVisibles.size();
    bestiole.setOrientation(mOrientation);
}



T * ComportementGregaire::getCouleur() const {
    return COULEUR_CFG;
}

void ComportementGregaire::initFromConfig() {
    // par defaut : orange
    COULEUR_CFG[0] = Config::getInstance().getInt("GREG_COULEUR_R", 255);
    COULEUR_CFG[1] = Config::getInstance().getDouble("GREG_COULEUR_G", 128);
    COULEUR_CFG[2] = Config::getInstance().getDouble("GREG_COULEUR_B", 0);
}