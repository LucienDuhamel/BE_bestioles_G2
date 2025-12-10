#ifndef _Comportement_
#define _Comportement_

#include "config.h"
#include "UImg.h"

#include <iostream>
#include <vector>
#include <string> 

class Bestiole;
class EspeceBestiole;

class Comportement
{

public :
   virtual ~Comportement( )= default;
   virtual Comportement* clone() const = 0;
   virtual void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) = 0;
   virtual T * getCouleur() const = 0;
   virtual std::string getName() const = 0;
};


#endif