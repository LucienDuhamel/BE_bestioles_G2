#include "Bestiole.h"
#include "ComportementPeureux.h"
#include "utils.h"

#include <iostream>
#include <vector>

T ComportementPeureux::COULEUR_CFG[3] = {0, 0, 0};
int ComportementPeureux::BESTIOLE_SCARED_NUMBER = -1;
int ComportementPeureux::REMAINING_SCARED_STEPS = -1;
double ComportementPeureux::SPEED_COEF = -1.0;
bool ComportementPeureux::configInitialized = false;


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


Comportement* ComportementPeureux::clone() const {
    return new ComportementPeureux();
}


/**
 * @brief Comportement peureux : fuit en sens inverse du barycentre des menaces.
 * 
 * Si au moins N (paramètre de la config) bestioles sont détectées, la bestiole entre en mode panique :
 * elle fuit dans la direction opposée au barycentre du groupe, avec une vitesse accrue.
 * Le mode panique dure un nombre d'étapes configuré.
 * 
 * @param bestiole La bestiole qui adopte ce comportement
 * @param listeBestioles Liste de toutes les bestioles du milieu
 * 
 * @details
 * - Détecte les bestioles visibles
 * - Si nb_détectées >= BESTIOLE_SCARED_NUMBER : entrée en mode panique
 *   - Calcule le barycentre des positions
 *   - Oriente dans la direction opposée
 *   - Multiplie la vitesse par SPEED_COEF
 *   - Reste apeurée pendant REMAINING_SCARED_STEPS étapes
 * - Si nb_détectées < seuil : décrémente le compteur et restaure la vitesse normale
 * 
 * @note État par-instance : chaque bestiole peur a son propre temps de panique
 */
void ComportementPeureux::reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles)
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);
    
    double vIni = bestiole.getVitesseIni();

    // Si assez d'individus pour être effrayé
    if (static_cast<int>(bestiolesVisibles.size()) >= BESTIOLE_SCARED_NUMBER)
    {
        // Calcul du barycentre des positions des bestioles visibles
        double bx = 0.0, by = 0.0;
        for (EspeceBestiole* b : bestiolesVisibles) {
            bx += static_cast<double>(b->getX());
            by += static_cast<double>(b->getY());
        }
        bx /= static_cast<double>(bestiolesVisibles.size());
        by /= static_cast<double>(bestiolesVisibles.size());

        // Fuite : orientation opposée au barycentre
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
        // Si la bestiole est encore effrayée :
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


T * ComportementPeureux::getCouleur()  const  {
    return COULEUR_CFG;
}


void ComportementPeureux::initFromConfig() {
    // par defaut : vert clair
    COULEUR_CFG[0] = Config::getInstance().getInt("PEU_COULEUR_R", 34);
    COULEUR_CFG[1] = Config::getInstance().getDouble("PEU_COULEUR_G", 177);
    COULEUR_CFG[2] = Config::getInstance().getDouble("PEU_COULEUR_B", 76);

    BESTIOLE_SCARED_NUMBER = Config::getInstance().getInt("BESTIOLE_SCARED_NUMBER", 3);
    REMAINING_SCARED_STEPS = Config::getInstance().getInt("REMAINING_SCARED_STEPS", 2);
    SPEED_COEF = Config::getInstance().getDouble("SPEED_COEF", 5);
}