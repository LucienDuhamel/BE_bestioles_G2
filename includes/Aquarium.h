#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


//class Milieu;
#include "config.h"
#include "Milieu.h"


class Aquarium : public CImgDisplay
{

private :
   Milieu       * flotte;

   int            delay;
   static int NB_BESTIOLES_INIT;
public :
   Aquarium( int width, int height, int _delay );
   ~Aquarium( void );

   void initFromConfig();
   Milieu & getMilieu( void ) { return *flotte; }

   void run( void );

};


#endif
