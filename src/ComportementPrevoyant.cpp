#include "Bestiole.h"
#include "ComportementPrevoyant.h"
#include "utils.h" 

#include <iostream>
#include <vector>
#include <cmath>


T ComportementPrevoyant::COULEUR_CFG[3] = {0, 0, 0};
bool ComportementPrevoyant::configInitialized = false;
ComportementPrevoyant* ComportementPrevoyant::singletonPrevoyant = nullptr;

ComportementPrevoyant* ComportementPrevoyant::getInstance()  
{
    if (singletonPrevoyant == nullptr){
        singletonPrevoyant = new ComportementPrevoyant();

        if(!configInitialized) {
            singletonPrevoyant->initFromConfig();
            configInitialized = true;
        }
    }

    return  singletonPrevoyant;
}

Comportement* ComportementPrevoyant::clone() const {
    return getInstance();
}



/**
 * @brief Comportement prévoyant : anticipe les collisions et fuit proactivement.
 * 
 * La bestiole prédit la position future des menaces visibles en fonction
 * de leur trajectoire courante, et se détourne d'avance pour les éviter.
 * 
 * @param bestiole La bestiole qui adopte ce comportement
 * @param listeBestioles Liste de toutes les bestioles du milieu
 * 
 * @details
 * - Détecte les bestioles visibles
 * - Pour chaque visible :
 *   - Cas 1 (collision immédiate) : fuit perpendiculairement
 *   - Cas 2 (collision future) : prédit la position future de l'autre
 *     en extrapolant sa trajectoire (position + vitesse * direction)
 * - Accumule les vecteurs de fuite
 * - S'oriente dans la direction d'évitement globale
 * 
 * @note Utilise des zones de collision (hit boxes) pour anticiper les chocs.
 */
void ComportementPrevoyant::reagit(
    Bestiole& bestiole,
    const std::vector<EspeceBestiole*>& listeBestioles
)
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);
    if (bestiolesVisibles.empty())
        return;

    double bx = static_cast<double>(bestiole.getX());
    double by = static_cast<double>(bestiole.getY());
    double btheta = bestiole.getOrientation();
    double bv = bestiole.getVitesse();

    // Position future estimée
    double nbx = bx + bv * std::cos(btheta);
    double nby = by + bv * std::sin(btheta);

    double avoidX = 0.0;
    double avoidY = 0.0;

    for (EspeceBestiole* other : bestiolesVisibles)
    {
        if (!other || other == &bestiole)
            continue;

        double ox = static_cast<double>(other->getX());
        double oy = static_cast<double>(other->getY());

        // Cas 1 : Collision immédiate
        if (bestiole.isInCollisionWith(*other))
        {
            double dx = bx - ox;
            double dy = by - oy;
            double d = std::sqrt(dx*dx + dy*dy);

            if (d > 0) {
                avoidX += dx / d;
                avoidY += dy / d;
            }
            continue;
        }

        // Cas 2 : Anticipation (Position future de l'autre)
        double otheta = other->getOrientation();
        double ov = other->getVitesse();

        double nox = ox + ov * std::cos(otheta);
        double noy = oy + ov * std::sin(otheta);

        if (isInHitBox(nox, noy, other->getAffSize(),
                       nbx, nby, bestiole.getAffSize()))
        {
            // Fuite = direction opposée à la menace
            double ddx = bx - nox;
            double ddy = by - noy;
            double d = std::sqrt(ddx*ddx + ddy*ddy);
            if (d > 0) {
                avoidX += ddx / d;
                avoidY += ddy / d;
            }
        }
    }

    if (avoidX == 0.0 && avoidY == 0.0)
        return;

    // Calcul de la nouvelle orientation de fuite
    double newAngle = std::atan2(avoidY, avoidX);

    bestiole.setOrientation(newAngle);
}


T * ComportementPrevoyant::getCouleur()  const {
    return COULEUR_CFG;
}


void ComportementPrevoyant::initFromConfig() {
    // par defaut : bleu clair
    COULEUR_CFG[0] = Config::getInstance().getInt("PRE_COULEUR_R", 30);
    COULEUR_CFG[1] = Config::getInstance().getDouble("PRE_COULEUR_G", 144);
    COULEUR_CFG[2] = Config::getInstance().getDouble("PRE_COULEUR_B", 255);
}