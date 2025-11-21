#include "Bestiole.h"
#include "ComportementPrevoyant.h"
#include <iostream>
#include <vector>


ComportementPrevoyant* ComportementPrevoyant::singletonPrevoyant = nullptr;

ComportementPrevoyant*   ComportementPrevoyant::getInstance()
{
    if (singletonPrevoyant == nullptr)
        singletonPrevoyant = new ComportementPrevoyant();

    return  singletonPrevoyant;
}


#include "ComportementPrevoyant.h"
#include "Bestiole.h"
#include <cmath>

void ComportementPrevoyant::bouge(
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

    for (Bestiole* other : visibles)
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
