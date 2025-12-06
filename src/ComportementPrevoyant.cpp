#include "Bestiole.h"
#include "ComportementPrevoyant.h"
#include <iostream>
#include <vector>
#include <cmath>

T ComportementPrevoyant::couleur_cfg[3] = {0, 0, 0};
double ComportementPrevoyant::T_PREDICT = 0.0;
double ComportementPrevoyant::DIST_MIN_COLLISION = 0.0;
bool ComportementPrevoyant::configInitialized = false;
ComportementPrevoyant* ComportementPrevoyant::singletonPrevoyant = nullptr;

ComportementPrevoyant*   ComportementPrevoyant::getInstance()  
{
    if (singletonPrevoyant == nullptr){
        singletonPrevoyant = new ComportementPrevoyant();

        if(!configInitialized) {
            singletonPrevoyant->initFromConfig();
            configInitialized = true;
        }

        // Couleur bleu clair

    }

    return  singletonPrevoyant;
}
Comportement* ComportementPrevoyant::clone() const {
    // Just return the singleton
    return getInstance();
}

void ComportementPrevoyant::initFromConfig() {
    // par défaut : vert clair
    couleur_cfg[0] = Config::getInstance().getInt("PRE_COULEUR_R", 30);
    couleur_cfg[1] = Config::getInstance().getDouble("PRE_COULEUR_G", 144);
    couleur_cfg[2] = Config::getInstance().getDouble("PRE_COULEUR_B", 255);

    T_PREDICT = Config::getInstance().getDouble("T_PREDICT", 15.0);
    DIST_MIN_COLLISION = Config::getInstance().getDouble("DIST_MIN_COLLISION", 30.0);
}

T * ComportementPrevoyant::getCouleur()  const {
    return couleur_cfg;
}


void ComportementPrevoyant::reagit(
    Bestiole& bestiole,
    const std::vector<EspeceBestiole*>& listeBestioles
)
{
    const auto& visibles = bestiole.detecteBestioles(listeBestioles);
    if (visibles.empty())
        return;

    double bx = bestiole.getX();
    double by = bestiole.getY();
    double btheta = bestiole.getOrientation();
    double bv = bestiole.getVitesse();

    // Position future correcte
    double nbx = bx + bv * std::cos(btheta);
    double nby = by + bv * std::sin(btheta);

    double avoidX = 0.0;
    double avoidY = 0.0;

    for (EspeceBestiole* other : visibles)
    {
        if (!other || other == &bestiole)
            continue;

        double ox = other->getX();
        double oy = other->getY();

        // Collision immédiate
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

        // Position future de l'autre
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

    // Nouvelle orientation = fuite
    double newAngle = std::atan2(avoidY, avoidX);

    bestiole.setOrientation(newAngle);
}






