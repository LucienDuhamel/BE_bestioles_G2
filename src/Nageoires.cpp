#include "Nageoires.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

double Nageoires::vitesseMax = -1.0;
bool Nageoires::configInitialized = false;

Nageoires::Nageoires()
{   
    if (!configInitialized) {
        initFromConfig();
        configInitialized = true;
    }
    
    CoeffVitesseNageoires = 1.0 + (static_cast<double>(rand()) / RAND_MAX) * (vitesseMax - 1.0);
}

void Nageoires::draw(UImg& support, Bestiole* b)
{
    // Dessine un points violet sur la queue de la bestiole
    T couleurViolet[3] = {160, 32, 240}; // Violet
    int aff = static_cast<int>( std::round(b->getAffSize()) );
    int cx = b->getX() - static_cast<int>( std::cos(b->getOrientation()) * (0.8 * aff) );
    int cy = b->getY() - static_cast<int>( -std::sin(b->getOrientation()) * (0.8 * aff) );
    support.draw_circle(cx, cy, std::max(1, static_cast<int>(std::round(0.2 * aff))), couleurViolet);
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
    Nageoires::vitesseMax = cfg.getDouble("COEFF_VITESSE_NAGEOIRE_MAX", 10.0);
}