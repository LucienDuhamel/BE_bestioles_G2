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

   Aquarium       ecosysteme( 640, 480, 30 );
   ecosysteme.getMilieu().initConfig(30);
   





   ecosysteme.run();
   return 0;

}
