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

   const int WIDTH = Config::getInstance().getInt("WIDTH", 800.0);
   const int HEIGHT = Config::getInstance().getInt("HEIGHT", 600.0);
   const int DELAY = Config::getInstance().getInt("DELAY", 100.0);
   

   Aquarium       ecosysteme( WIDTH, HEIGHT, DELAY );
   

   ecosysteme.run();
   return 0;

}
