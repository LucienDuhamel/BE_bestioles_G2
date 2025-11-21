#include "Camouflage.h"
#include "Bestiole.h"
#include "UImg.h"

Camouflage::Camouflage()
{
    // Default constructor with default values
    camouflage = 0.6; // 60% camouflage effectiveness
}

Camouflage::Camouflage(double camouflage)
{
    this->camouflage = camouflage;
}

void Camouflage::draw(UImg& support, Bestiole* b)
{
    // Draw dark green stripes across the bestiole body
    T stripeColor[3] = {255, 255, 255}; // White stripes
    int cx = b->getX();
    int cy = b->getY();

    // Body ellipse approximate size (match AFF_SIZE used for drawing)
    // Can't access Bestiole::AFF_SIZE (private), use matching constants
    const int halfW = 8; // approx AFF_SIZE
    const int halfH = 3; // approx AFF_SIZE/3

    // Draw several parallel stripes perpendicular to the orientation
    double theta = b->getOrientation();
    // perpendicular direction
    double px = std::cos(theta + M_PI/2.0);
    double py = -std::sin(theta + M_PI/2.0);

    int stripes = 3;
    for (int i = -stripes; i <= stripes; ++i) {
        double t = (double)i / (double)(stripes + 1);
        // position along body axis
        double ax = std::cos(theta) * (t * halfW);
        double ay = -std::sin(theta) * (t * halfW);

        int x1 = cx + static_cast<int>(ax + px * (-halfH));
        int y1 = cy + static_cast<int>(ay + py * (-halfH));
        int x2 = cx + static_cast<int>(ax + px * (halfH));
        int y2 = cy + static_cast<int>(ay + py * (halfH));

        support.draw_line(x1, y1, x2, y2, stripeColor);
    }
}
void Camouflage::setCamouflage(Bestiole* b){

    b->setCamouflage(this->camouflage);
}
Camouflage* Camouflage::clone() const {
    return new Camouflage(camouflage);
}