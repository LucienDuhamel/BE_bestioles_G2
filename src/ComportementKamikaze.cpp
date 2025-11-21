#include "Bestiole.h"
#include "ComportementKamikaze.h"
#include "utils.h"

void ComportementKamikaze::bouge(Bestiole& b) const
{
    const auto& liste = b.getListeBestiolesDetectees();

    if (liste.empty())
        return; // rien à poursuivre

    // Bestiole la plus proche au début
    Bestiole* targeted = liste[0];
    double minDistance = calcDistance(b, *targeted);

    // Trouver la bestiole la plus proche
    for (Bestiole* other : liste)
    {
        double d = calcDistance(b, *other);
        if (d < minDistance)
        {
            minDistance = d;
            targeted = other;
        }
    }

    // Ajuster l'orientation vers la cible
    b.setOrientation( calcOrientation(b, *targeted) );
}


string ComportementKamikaze::getNameComportement() const
{
    return "kamikaze";
}