#include "Bestiole.h"
#include "ComportementGregaire.h"
#include <iostream>
#include <vector>

ComportementGregaire* ComportementGregaire::singletonGregaire = nullptr;

ComportementGregaire*  ComportementGregaire::getInstance()
{
    if (singletonGregaire == nullptr)
        singletonGregaire = new ComportementGregaire();

    return  singletonGregaire;
}

void ComportementGregaire::bouge( Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles) const
{
    const auto& liste = bestiole.detecteBestioles(listeBestioles);

    if (liste.empty()) return;   // éviter division par zéro

    double mOrientation = 0.0;

    for (Bestiole* b : liste) {
        mOrientation += b->getOrientation();
    }

    mOrientation /= liste.size();
    bestiole.setOrientation(mOrientation);
}
