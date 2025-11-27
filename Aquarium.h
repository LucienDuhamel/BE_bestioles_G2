#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include <CImg.h>
#include <cstdio>

using namespace std;
using namespace cimg_library;


//class Milieu;
#include "Milieu.h"
#include "Simulation.h"


class Aquarium : public CImgDisplay
{

private :
   Milieu       * flotte;

   Simulation  * simulation;

   int            delay;

public :
   Aquarium( int width, int height, int _delay );
   ~Aquarium( void );

   Milieu & getMilieu( void ) { return *flotte; }

   void run( void );

};


#endif
