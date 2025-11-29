#ifndef _Comportement_
#define _Comportement_

#include "config.h"
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
   virtual std::string getNom() const = 0;
   virtual void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const = 0;

};


#endif
