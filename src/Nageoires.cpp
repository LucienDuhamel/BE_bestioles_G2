#include "Nageoires.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

Nageoires::Nageoires()
{
    Config& cfg = Config::getInstance();
    double vitesseMax = cfg.getDouble("COEFF_VITESSE_NAGEOIRE_MAX");
    
    CoeffVitesseNageoires = 1.0 + (static_cast<double>(rand()) / RAND_MAX) * (vitesseMax - 1.0);
}

void Nageoires::draw(UImg& support, Bestiole* b)
{
    // Dessine un points violet sur la queue de la bestiole
    T couleurViolet[3] = {160, 32, 240}; // Violet
    int cx = b->getX() - static_cast<int>( std::cos(b->getOrientation()) * 12 );
    int cy = b->getY() - static_cast<int>( -std::sin(b->getOrientation()) * 12 );
    support.draw_circle(cx, cy, 3, couleurViolet);
}
void Nageoires::setVitesseNageoires(Bestiole* b) {
    double nouvelleVitesse = b->getVitesse() * CoeffVitesseNageoires;

    b->setVitesse(nouvelleVitesse);
}
Nageoires* Nageoires::clone() const {
    Nageoires* n = new Nageoires();
    n->CoeffVitesseNageoires = this->CoeffVitesseNageoires;
    return n;
}