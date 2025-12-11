#include "Camouflage.h"
#include "Bestiole.h"
#include "UImg.h"
#include "config.h"
#include <cstdlib>

double Camouflage::camoMin = -1.0;
double Camouflage::camoMax = -1.0;
bool Camouflage::configInitialized = false;

Camouflage::Camouflage()
{   
    if (!configInitialized) {
        initFromConfig();
        configInitialized = true;
    }
    
    camouflage = camoMin + (static_cast<double>(rand()) / RAND_MAX) * (camoMax - camoMin);
}

void Camouflage::draw(UImg& support, Bestiole* b)
{
    // Définition des rayures qui vont symboliser le camouflage
    T stripeColor[3] = {255, 255, 255}; //Rayures blanches
    int cx = b->getX();
    int cy = b->getY();

    // Utilise des constante que se rapproche de aff_size
    int aff = static_cast<int>( std::round(b->getAffSize()) );
    const int halfW = std::max(1, static_cast<int>(std::round(0.9 * aff)));
    const int halfH = std::max(1, static_cast<int>(std::round(aff / 3.0)));

    // Dessine les rayures parrallèlement au corp de la bestiole
    double theta = b->getOrientation();
    double px = std::cos(theta + M_PI/2.0);
    double py = -std::sin(theta + M_PI/2.0);

    int stripes = std::min(6, std::max(1, aff / 6));
    for (int i = -stripes; i <= stripes; ++i) {
        double t = (double)i / (double)(stripes + 1);
        double ax = std::cos(theta) * (t * halfW);
        double ay = -std::sin(theta) * (t * halfW);

        int x1 = cx + static_cast<int>(ax + px * (-halfH));
        int y1 = cy + static_cast<int>(ay + py * (-halfH));
        int x2 = cx + static_cast<int>(ax + px * (halfH));
        int y2 = cy + static_cast<int>(ay + py * (halfH));

        support.draw_line(x1, y1, x2, y2, stripeColor);
    }
}
void Camouflage::setParameters(Bestiole* b) const
{
    setCamouflage(b);
}
void Camouflage::setCamouflage(Bestiole* b) const {

    b->setCamouflage(this->camouflage);
}
Camouflage* Camouflage::clone() const {
    Camouflage* c = new Camouflage();
    c->camouflage = this->camouflage;
    return c;
}


void Camouflage::initFromConfig(){
    Config& cfg = Config::getInstance();
    Camouflage::camoMin = cfg.getDouble("CAMOUFLAGE_MIN", 0.0);
    Camouflage::camoMax = cfg.getDouble("CAMOUFLAGE_MAX", 1.0);
}