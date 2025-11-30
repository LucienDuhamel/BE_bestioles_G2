#include "Oreilles.h"
#include "Bestiole.h"
#include "UImg.h"

Oreilles::Oreilles()
{
    // Constructeur par défault
    distanceVisionOreilles = 80.0;      
    pourcentageDetectionOreilles = 0.8; 
}

Oreilles::Oreilles(double distanceVisionOreilles, double pourcentageDetectionOreilles)
{
    this->distanceVisionOreilles = distanceVisionOreilles;
    this->pourcentageDetectionOreilles = pourcentageDetectionOreilles;
}


void Oreilles::draw(UImg& support, Bestiole* b)
{
    // Dessine deux points noir sur les côtés de la bestiole
    T couleurOreilles[3] = {0, 0, 0}; // noir
    double theta = b->getOrientation();
    int x = b->getX();
    int y = b->getY();

    // definition position oreilles
    const double side = 5.0;    // offset lateral
    const double forward = 3.0; // offset frontal 
    const int rayon = 1.75;        // rayon des points

    int lx = x + static_cast<int>( std::cos(theta + M_PI/2.0) * side + std::cos(theta) * forward );
    int ly = y + static_cast<int>( -std::sin(theta + M_PI/2.0) * side + -std::sin(theta) * forward );

    int rx = x + static_cast<int>( std::cos(theta - M_PI/2.0) * side + std::cos(theta) * forward );
    int ry = y + static_cast<int>( -std::sin(theta - M_PI/2.0) * side + -std::sin(theta) * forward );

    support.draw_circle(lx, ly, rayon, couleurOreilles);
    support.draw_circle(rx, ry, rayon, couleurOreilles);
}
std::vector<Bestiole*> Oreilles::detecter( std::vector<Bestiole*> listeBestioles, Bestiole* b )
{
    std::vector<Bestiole*> ListeBestiolesDetectees;
    
    for (Bestiole* autre: listeBestioles) {
        if (autre != b) {
            // Calcul de la distance entre les deux bestioles
            double dx = autre->getX() - b->getX();
            double dy = autre->getY() - b->getY();
            double distance = std::sqrt(dx * dx + dy * dy);

            // Vérification si la bestiole est dans le champ de détection des oreilles
            if (distance <= distanceVisionOreilles) {

                // Application de la règle de détection
                if (pourcentageDetectionOreilles > autre->getCamouflage()) {
                    ListeBestiolesDetectees.push_back(autre);
                }
            }
        }
    }
    return ListeBestiolesDetectees;
}   

Oreilles* Oreilles::clone() const {
    return new Oreilles(distanceVisionOreilles, pourcentageDetectionOreilles);
}