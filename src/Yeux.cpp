#include "Yeux.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

double Yeux::angleMin = -1.0;
double Yeux::angleMax = -1.0;
double Yeux::distMin = -1.0;
double Yeux::distMax = -1.0;
double Yeux::pourcMin = -1.0;
double Yeux::pourcMax = -1.0;
bool Yeux::configInitialized = false;

Yeux::Yeux()
{    
    if(!configInitialized) {
        initFromConfig();
        configInitialized = true;
    }
    angleVisionYeux = angleMin + (static_cast<double>(rand()) / RAND_MAX) * (angleMax - angleMin);
    distanceVisionYeux = distMin + (static_cast<double>(rand()) / RAND_MAX) * (distMax - distMin);
    pourcentageDetectionYeux = pourcMin + (static_cast<double>(rand()) / RAND_MAX) * (pourcMax - pourcMin);
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

std::vector<EspeceBestiole*> Yeux::detecter( std::vector<EspeceBestiole*> listeBestioles, Bestiole* b )
{
    std::vector<EspeceBestiole*> ListeBestiolesDetectees;

    for (EspeceBestiole* autre: listeBestioles) {
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
    Yeux* y = new Yeux();
    y->angleVisionYeux = this->angleVisionYeux;
    y->distanceVisionYeux = this->distanceVisionYeux;
    y->pourcentageDetectionYeux = this->pourcentageDetectionYeux;
    return y;
}


void Yeux::initFromConfig(){
    Config& cfg = Config::getInstance();
    Yeux::angleMin = cfg.getDouble("ANGLE_VISION_OEUIL_MIN", M_PI/6);
    Yeux::angleMax = cfg.getDouble("ANGLE_VISION_OEUIL_MAX", M_PI);
    Yeux::distMin = cfg.getDouble("DISTANCE_VISION_OEUIL_MIN", 10.0);
    Yeux::distMax = cfg.getDouble("DISTANCE_VISION_OEUIL_MAX", 100.0);
    Yeux::pourcMin = cfg.getDouble("POURCENTAGE_DETECTION_OEUIL_MIN", 0.01);
    Yeux::pourcMax = cfg.getDouble("POURCENTAGE_DETECTION_OEUIL_MAX", 0.9);
}