#include "Nageoires.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

double Nageoires::vitesseMax = -1.0;

Nageoires::Nageoires()
{   
    if (vitesseMax < 0.0)
        initFromConfig();
    
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
void Nageoires::setParameters(Bestiole* b) const
{
    setVitesseNageoires(b);
}

void Nageoires::setVitesseNageoires(Bestiole* b) const {
    double nouvelleVitesse = b->getVitesse() * CoeffVitesseNageoires;

    b->setVitesse(nouvelleVitesse);
}
Nageoires* Nageoires::clone() const {
    Nageoires* n = new Nageoires();
    n->CoeffVitesseNageoires = this->CoeffVitesseNageoires;
    return n;
}

void Nageoires::initFromConfig() {
    Config& cfg = Config::getInstance();
    Nageoires::vitesseMax = cfg.getDouble("COEFF_VITESSE_NAGEOIRE_MAX");
}