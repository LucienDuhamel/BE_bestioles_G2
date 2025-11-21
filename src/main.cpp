#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Yeux.h"
#include "Oreilles.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Camouflage.h"

#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    Aquarium ecosysteme(640, 480, 30);
    Milieu& milieu = ecosysteme.getMilieu();

    // Add several random Bestioles with random combinations
    srand(static_cast<unsigned int>(time(nullptr)));
    const int extra = 20; // add 10 more
    for (int i = 0; i < extra; ++i) {
        Bestiole bx;
        // randomly choose accessories/sensors
        int r = rand() % 4;
        if (r == 0) { bx.addAccessoire(new Carapace()); }
        else if (r == 1) { bx.addAccessoire(new Nageoires()); }
        else if (r == 2) { bx.addAccessoire(new Camouflage()); }
        else { bx.addAccessoire(new Carapace()); bx.addAccessoire(new Nageoires()); }

        if (rand() % 2) bx.addCapteur(new Yeux());
        if (rand() % 3 == 0) bx.addCapteur(new Oreilles());

        milieu.addMember(bx);
    }

    ecosysteme.run();

    return 0;
}
