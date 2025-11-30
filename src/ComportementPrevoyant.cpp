#include "Bestiole.h"
#include "ComportementPrevoyant.h"
#include <iostream>
#include <vector>
#include <cmath>

T ComportementPrevoyant::couleur_cfg[3] = {0, 0, 0};
double ComportementPrevoyant::T_PREDICT = 0.0;
double ComportementPrevoyant::DIST_MIN_COLLISION = 0.0;

ComportementPrevoyant* ComportementPrevoyant::singletonPrevoyant = nullptr;

ComportementPrevoyant*   ComportementPrevoyant::getInstance()
{
    if (singletonPrevoyant == nullptr){
        singletonPrevoyant = new ComportementPrevoyant();
        singletonPrevoyant->couleur = new T[ 3 ];

        if((couleur_cfg[0]==0 && couleur_cfg[1]==0 && couleur_cfg[2]==0)
            || T_PREDICT==0.0 || DIST_MIN_COLLISION==0.0) {
            singletonPrevoyant->initFromConfig();
        }

        // Couleur bleu clair
        singletonPrevoyant->couleur[ 0 ] = couleur_cfg[0];
        singletonPrevoyant->couleur[ 1 ] = couleur_cfg[1];
        singletonPrevoyant->couleur[ 2 ] = couleur_cfg[2];

    }

    return  singletonPrevoyant;
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
    return couleur;
}


void ComportementPrevoyant::reagit(
    Bestiole& bestiole,
    const std::vector<EspeceBestiole*>& listeBestioles
) const
{
    // Bestioles visibles
    const auto& visibles = bestiole.detecteBestioles(listeBestioles);

    if (visibles.empty())
        return;

    double bx = bestiole.getX();
    double by = bestiole.getY();
    double vx = bestiole.getVitesse() * cos(bestiole.getOrientation());
    double vy = bestiole.getVitesse() * sin(bestiole.getOrientation());

    // position future du bestiole prévoyant
    double bx_future = bx + vx * T_PREDICT;
    double by_future = by + vy * T_PREDICT;

    // vecteur résultant d'évitement
    double avoidX = 0.0;
    double avoidY = 0.0;

    for (EspeceBestiole* other : visibles)
    {
        if (other == nullptr)
            continue;

        // position autre
        double ox = other->getX();
        double oy = other->getY();
        double ovx = other->getVitesse() * cos(other->getOrientation());
        double ovy = other->getVitesse() * sin(other->getOrientation());

        // position future autre bestiole
        double ox_future = ox + ovx * T_PREDICT;
        double oy_future = oy + ovy * T_PREDICT;

        // distance future
        double dx = bx_future - ox_future;
        double dy = by_future - oy_future;
        double distFuture = std::sqrt(dx*dx + dy*dy);

        if (distFuture < DIST_MIN_COLLISION)
        {
            // vecteur d'évitement : s’éloigner du point futur
            avoidX += dx / distFuture;
            avoidY += dy / distFuture;
        }
    }

    // Aucun risque détecté → continuer tout droit
    if (avoidX == 0.0 && avoidY == 0.0)
        return;

    // Calcul de la nouvelle orientation
    double newAngle = std::atan2(avoidY, avoidX);

    // Ajustement vers une trajectoire d'évitement
    bestiole.setOrientation(newAngle);
}
