#include "Aquarium.h"

#include <iostream>

using namespace std;


int main()
{
   int delay = 100; // délai en ms, 30ms avant changement
   int width = 1280;
   int height = 960;
   Aquarium       ecosysteme( width, height, delay );

   
   ecosysteme.getMilieu().initConfig(30);
   
   ecosysteme.run();


   return 0;

}
