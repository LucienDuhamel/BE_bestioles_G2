#include "Oreilles.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

double Oreilles::distMin = -1.0;
double Oreilles::distMax = -1.0;
double Oreilles::pourcMin = -1.0;
double Oreilles::pourcMax = -1.0;

Oreilles::Oreilles()
{   

    if(distMin < 0.0 || distMax < 0.0 || pourcMin < 0.0 || pourcMax < 0.0)
        initFromConfig();
    distanceVisionOreilles = distMin + (static_cast<double>(rand()) / RAND_MAX) * (distMax - distMin);
    pourcentageDetectionOreilles = pourcMin + (static_cast<double>(rand()) / RAND_MAX) * (pourcMax - pourcMin);
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
std::vector<EspeceBestiole*> Oreilles::detecter( std::vector<EspeceBestiole*> listeBestioles, Bestiole* b )
{
    std::vector<EspeceBestiole*> ListeBestiolesDetectees;
    
    for (EspeceBestiole* autre: listeBestioles) {
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
    Oreilles* o = new Oreilles();
    o->distanceVisionOreilles = this->distanceVisionOreilles;
    o->pourcentageDetectionOreilles = this->pourcentageDetectionOreilles;
    return o;
}


void Oreilles::initFromConfig() {
    Config& cfg = Config::getInstance();
    Oreilles::distMin = cfg.getDouble("DISTANCE_VISION_OREILLE_MIN");
    Oreilles::distMax = cfg.getDouble("DISTANCE_VISION_OREILLE_MAX");
    Oreilles::pourcMin = cfg.getDouble("POURCENTAGE_DETECTION_OREILLE_MIN");
    Oreilles::pourcMax = cfg.getDouble("POURCENTAGE_DETECTION_OREILLE_MAX");
}