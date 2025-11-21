#include "Yeux.h"
#include "Bestiole.h"
#include "UImg.h"

Yeux::Yeux()
{
    // Default constructor with default values
    angleVisionYeux = M_PI / 3;        // 60 degree vision
    distanceVisionYeux = 50.0;         // 50 unit range
    pourcentageDetectionYeux = 0.7;    // 70% detection
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

    // Dessine deux points cyan sur les côtés de la tête de la bestiole
    const double side = 2.0;    // small lateral offset
    const double forward = 10.0; // in front of the head
    const int rayon = 1.5;        // a bit larger

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
