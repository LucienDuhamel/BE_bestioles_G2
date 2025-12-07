#include "Aquarium.h"

#include <iostream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 640, 480, 30 );

   
   ecosysteme.getMilieu().initConfig(30);
   
   ecosysteme.run();


   return 0;

}
