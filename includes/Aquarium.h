#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

#include "config.h"
#include "Milieu.h"
#include "Simulation.h" 


class Aquarium : public CImgDisplay
{

private :
   Milieu       * flotte;
   Simulation   * simulation; 

   int            delay;

   // Paramètres de configuration du Main
   static int NB_BESTIOLES_INIT;
   static int GRAPHIC_WIDTH;
   static int GRAPHIC_HEIGHT;
   static bool ACTIVATED_ANALYSE;
   static bool configInitialized;

public :
   Aquarium( int width, int height, int _delay );
   ~Aquarium( void );

   void initFromConfig();

   Milieu & getMilieu( void ) { return *flotte; }

   void run( void );

};


#endif