#ifndef _Comportement_
#define _Comportement_


#include "EspeceBestiole.h"
#include "UImg.h"

#include <iostream>
#include <vector>

class Bestiole;

class Comportement
{

public :
   
   virtual ~Comportement( void )= default;
   virtual T * getCouleur() const = 0;
   virtual void bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const = 0;

};


#endif
