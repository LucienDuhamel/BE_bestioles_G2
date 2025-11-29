#include "Carapace.h"
#include "Bestiole.h"
#include "UImg.h"

// Constructeur par defaut
Carapace::Carapace()
{
    CoeffVitesseCarapace =  10; 
    CoeffResistanceCarapace = 5;   
}

Carapace::Carapace(double CoeffVitesseCarapace ,double CoeffResistanceCarapace)
{
    this->CoeffVitesseCarapace = CoeffVitesseCarapace;
    this->CoeffResistanceCarapace = CoeffResistanceCarapace;
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
    return new Carapace(CoeffVitesseCarapace, CoeffResistanceCarapace);
}
