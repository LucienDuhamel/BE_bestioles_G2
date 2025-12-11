#include "Oreilles.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

double Oreilles::distMin = -1.0;
double Oreilles::distMax = -1.0;
double Oreilles::pourcMin = -1.0;
double Oreilles::pourcMax = -1.0;
bool Oreilles::configInitialized = false;

Oreilles::Oreilles()
{   

    if(!configInitialized) {
        initFromConfig();
        configInitialized = true;
    }
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
    int aff = static_cast<int>( std::round(b->getAffSize()) );

    // definition position oreilles (proportionnelles à AFF_SIZE)
    const double side = 0.50 * aff;      // offset lateral
    const double forward = 0.45 * aff;   // offset frontal 
    const int rayon = std::max(1, static_cast<int>(std::round(0.1 * aff)));  // rayon des points

    double cosTheta = std::cos(theta);
    double sinTheta = std::sin(theta);
    double cosSide = std::cos(theta + M_PI/2.0);
    double sinSide = std::sin(theta + M_PI/2.0);

    int lx = x + static_cast<int>( cosSide * side + cosTheta * forward );
    int ly = y + static_cast<int>( -sinSide * side - sinTheta * forward );

    int rx = x + static_cast<int>( -cosSide * side + cosTheta * forward );
    int ry = y + static_cast<int>( sinSide * side - sinTheta * forward );

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
    Oreilles::distMin = cfg.getDouble("DISTANCE_VISION_OREILLE_MIN", 10.0);
    Oreilles::distMax = cfg.getDouble("DISTANCE_VISION_OREILLE_MAX", 100.0);
    Oreilles::pourcMin = cfg.getDouble("POURCENTAGE_DETECTION_OREILLE_MIN", 0.01);
    Oreilles::pourcMax = cfg.getDouble("POURCENTAGE_DETECTION_OREILLE_MAX", 0.9);
}