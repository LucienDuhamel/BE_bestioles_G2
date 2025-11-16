#ifndef _Comportement_
#define _Comportement_


//#include "Bestiole.h"

#include <iostream>
#include <vector>

class Bestiole;

class Comportement
{

public :
   virtual ~Comportement( void )= default;

   virtual void bouge(Bestiole bestiole, std::vector<Bestiole>   listeBestioles ) const = 0;

};


#endif
