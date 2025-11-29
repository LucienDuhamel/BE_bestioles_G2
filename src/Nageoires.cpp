#include "Nageoires.h"
#include "Bestiole.h"
#include "UImg.h"

Nageoires::Nageoires()
{
    // Constructeur par défault
    CoeffVitesseNageoires = 40; 
}

Nageoires::Nageoires(double CoeffVitesseNageoires)
{
    this->CoeffVitesseNageoires = CoeffVitesseNageoires;
}

void Nageoires::draw(UImg& support, Bestiole* b)
{
    // Dessine un points violet sur la queue de la bestiole
    T couleurViolet[3] = {160, 32, 240}; // Violet
    int cx = b->getX() - static_cast<int>( std::cos(b->getOrientation()) * 12 );
    int cy = b->getY() - static_cast<int>( -std::sin(b->getOrientation()) * 12 );
    support.draw_circle(cx, cy, 3, couleurViolet);
}
void Nageoires::setVitesseNageoires(Bestiole* b){

    b->setVitesse(b->getVitesse() * CoeffVitesseNageoires);
}
Nageoires* Nageoires::clone() const {
    return new Nageoires(CoeffVitesseNageoires);
}