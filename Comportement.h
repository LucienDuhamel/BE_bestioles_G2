#ifndef _Comportement_
#define _Comportement_


#include "EspeceBestiole.h"

#include <iostream>
#include <vector>

class Bestiole;

class Comportement
{

public :
   virtual ~Comportement( void )= default;

   virtual void bouge(Bestiole bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const = 0;

};


#endif
