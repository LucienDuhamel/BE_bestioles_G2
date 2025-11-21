#include "Bestiole.h"
#include "ComportementGregaire.h"

#include <memory>


void ComportementGregaire::bouge(Bestiole& b, std::vector< unique_ptr<Bestiole> > listeBestioles) const
{
    double mOrientation = 0.0;
    const auto& liste = b.detecteBestioles(listeBestioles);

    for (Bestiole* bDetectee : liste)
    {
        mOrientation += bDetectee->getOrientation();
    }

    mOrientation /= liste.size();
    b.setOrientation(mOrientation);
}

string ComportementGregaire::getNameComportement() const
{
    return "gregaire";
}
