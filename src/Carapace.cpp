#include "Carapace.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

double Carapace::vitesseMax = -1.0;
double Carapace::resistMax = -1.0;

Carapace::Carapace()
{
    if (vitesseMax <0.0 || resistMax <0.0)
        initFromConfig();    
    CoeffVitesseCarapace = 1.0 + (static_cast<double>(rand()) / RAND_MAX) * (vitesseMax - 1.0);
    CoeffResistanceCarapace = 1.0 + (static_cast<double>(rand()) / RAND_MAX) * (resistMax - 1.0);
}

void Carapace::draw(UImg& support, Bestiole* b)
{
    // Dessine une carapace bleu clair autour de la bestiole
    T couleurGold[3] = {173,216,230}; // bleu clair
    int cx = b->getX();
    int cy = b->getY();
    int rayon = 14; 
    float opacity = 0.25f;
    support.draw_circle(cx, cy, rayon, couleurGold, opacity);
}

void Carapace::setVitesseCarapace(Bestiole* b){

    b->setVitesse(b->getVitesse() / CoeffVitesseCarapace);
}

void Carapace::setResistanceCarapace(Bestiole* b){

    b->setResistance(CoeffResistanceCarapace);

}
Carapace* Carapace::clone() const {
    Carapace* c = new Carapace();
    c->CoeffVitesseCarapace = this->CoeffVitesseCarapace;
    c->CoeffResistanceCarapace = this->CoeffResistanceCarapace;
    return c;
}

void Carapace::initFromConfig(){
    Config& cfg = Config::getInstance();
    Carapace::vitesseMax = cfg.getDouble("COEFF_VITESSE_CARAPACE_MAX");
    Carapace::resistMax = cfg.getDouble("COEFF_RESISTANCE_CARAPACE_MAX");
}
