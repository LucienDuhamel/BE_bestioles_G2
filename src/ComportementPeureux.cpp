#include "Bestiole.h"
#include "ComportementPeureux.h"
#include "utils.h"

#include <iostream>
#include <vector>

T ComportementPeureux::couleur_cfg[3] = {0, 0, 0};
int ComportementPeureux::BESTIOLE_SCARED_NUMBER = -1;
int ComportementPeureux::REMAINING_SCARED_STEPS = -1;
double ComportementPeureux::SPEED_COEF = -1.0;
bool ComportementPeureux::configInitialized = false;

// Constructeur (Pas de Singleton ici, chaque bestiole a son instance)
ComportementPeureux::ComportementPeureux()
{   
    nbStep = 0;
    isScared = false;

    if(!configInitialized) {
            initFromConfig();
            configInitialized = true;
        }
}

ComportementPeureux::~ComportementPeureux() {}

// Clone obligatoire pour la Factory
Comportement* ComportementPeureux::clone() const {
    return new ComportementPeureux();
}

void ComportementPeureux::initFromConfig() {
    // par defaut : vert clair
    couleur_cfg[0] = Config::getInstance().getInt("PEU_COULEUR_R", 34);
    couleur_cfg[1] = Config::getInstance().getDouble("PEU_COULEUR_G", 177);
    couleur_cfg[2] = Config::getInstance().getDouble("PEU_COULEUR_B", 76);

    BESTIOLE_SCARED_NUMBER = Config::getInstance().getInt("BESTIOLE_SCARED_NUMBER", 3);
    REMAINING_SCARED_STEPS = Config::getInstance().getInt("REMAINING_SCARED_STEPS", 2);
    SPEED_COEF = Config::getInstance().getDouble("SPEED_COEF", 5);
}

T * ComportementPeureux::getCouleur()  const  {
    return couleur_cfg;
}

void ComportementPeureux::reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles)
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);
    
    // On récupère la vitesse de base stockée dans la bestiole (ajout du Main)
    double vIni = bestiole.getVitesseIni();

    // Si assez d'individus pour être effrayé
    if (static_cast<int>(bestiolesVisibles.size()) >= BESTIOLE_SCARED_NUMBER)
    {
        // Calcul du barycentre des positions
        double bx = 0.0, by = 0.0;
        for (EspeceBestiole* b : bestiolesVisibles) {
            bx += static_cast<double>(b->getX());
            by += static_cast<double>(b->getY());
        }
        bx /= static_cast<double>(bestiolesVisibles.size());
        by /= static_cast<double>(bestiolesVisibles.size());

        // Fuite : orientation opposée au barycentre
        // Utilisation de utils.h et des accesseurs avec Majuscules
        bestiole.setOrientation(calcOrientation(bestiole.getX(), bestiole.getY(), bx, by) + M_PI);

        // Activation du mode "effrayé"
        if (!isScared)
        {
            isScared = true;
            bestiole.setVitesse(vIni * SPEED_COEF);
        }

        nbStep = REMAINING_SCARED_STEPS;
    }
    else
    {
        // Encore effrayée ?
        if (nbStep > 0)
        {
            nbStep--;

            if (nbStep == 0)
            {
                // Retour vitesse normale
                bestiole.setVitesse(vIni);
                isScared = false;
            }
        }
    }
}