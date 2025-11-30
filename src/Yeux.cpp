#include "Yeux.h"
#include "Bestiole.h"
#include "UImg.h"

//Constructeur par default
Yeux::Yeux()
{
    angleVisionYeux = M_PI / 3;   
    distanceVisionYeux = 25;      
    pourcentageDetectionYeux = 0.8;   
}

Yeux::Yeux(double angleVisionYeux, double distanceVisionYeux, double pourcentageDetectionYeux)
{
    this->angleVisionYeux = angleVisionYeux;
    this->distanceVisionYeux = distanceVisionYeux;
    this->pourcentageDetectionYeux = pourcentageDetectionYeux;
}

void Yeux::draw(UImg& support, Bestiole* b)
{
    // dessine deux points cyan 
    T couleurYeux[3] = {0, 255, 255}; 
    double theta = b->getOrientation();
    int x = b->getX();
    int y = b->getY();

    // Dessine deux points bleu sur les côtés de la tête de la bestiole
    const double side = 3.0;    // offset latéral
    const double forward = 9.5; // offset frontal
    const int rayon = 1.75;        // rayon du point

    int lx = x + static_cast<int>( std::cos(theta + M_PI/2.0) * side + std::cos(theta) * forward );
    int ly = y + static_cast<int>( -std::sin(theta + M_PI/2.0) * side + -std::sin(theta) * forward );

    int rx = x + static_cast<int>( std::cos(theta - M_PI/2.0) * side + std::cos(theta) * forward );
    int ry = y + static_cast<int>( -std::sin(theta - M_PI/2.0) * side + -std::sin(theta) * forward );

    support.draw_circle(lx, ly, rayon, couleurYeux);
    support.draw_circle(rx, ry, rayon, couleurYeux);
}

std::vector<Bestiole*> Yeux::detecter( std::vector<Bestiole*> listeBestioles, Bestiole* b )
{
    std::vector<Bestiole*> ListeBestiolesDetectees;

    for (Bestiole* autre: listeBestioles) {
        if (autre != b) {
            // Calcul de la distance entre les deux bestioles
            double dx = autre->getX() - b->getX();
            double dy = autre->getY() - b->getY();
            double distance = std::sqrt(dx * dx + dy * dy);

            // Vérification si la bestiole est plus loin que la distance de vision des yeux
            if (distance <= distanceVisionYeux) {
                // Calcul de l'angle entre b et l'autre
                double angleBAutre = std::atan2(dy, dx);
                //Récupération de la direction de b
                double directionB = b->getOrientation();
                // Calcul de la différence angulaire
                double diff = std::fabs(directionB - angleBAutre);
                // Normalisation de la différence angulaire entre 0 et π
                if (diff > M_PI){
                    diff = 2 * M_PI - diff;
                }
                //  Vérification si l'autre bestiole est dans le champ de vision des yeux
                if (diff > angleVisionYeux / 2.0){
                    // Application de la règle de détection
                    if (pourcentageDetectionYeux > autre->getCamouflage()) {
                        ListeBestiolesDetectees.push_back(autre);
                    }
               }
            }
        }
    }
    return ListeBestiolesDetectees;
}

Yeux* Yeux::clone() const {
    return new Yeux(angleVisionYeux, distanceVisionYeux, pourcentageDetectionYeux);
}
