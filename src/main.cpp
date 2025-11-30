#include "Aquarium.h"
#include "utils.h"
#include "config.h"

#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


int main()
{  
   Config::getInstance().load("config.txt");

   const int WIDTH = Config::getInstance().getInt("WIDTH");
   const int HEIGHT = Config::getInstance().getInt("HEIGHT");
   const int DELAY = Config::getInstance().getInt("DELAY");
   const int NB_BESTIOLES_INIT = Config::getInstance().getInt("NB_BESTIOLES_INIT");

   Aquarium       ecosysteme( WIDTH, HEIGHT, DELAY );
   
   ecosysteme.getMilieu().initConfig(NB_BESTIOLES_INIT);
   





   ecosysteme.run();
   return 0;

}
