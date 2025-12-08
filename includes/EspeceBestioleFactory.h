#ifndef _EspeceBestioleFactory_
#define _EspeceBestioleFactory_

#include "config.h"
#include "EspeceBestiole.h"


class EspeceBestioleFactory
{

public :
   virtual ~EspeceBestioleFactory( void )= default;
   static bool configInitialized;
   virtual EspeceBestiole* creerEspeceBestiole() const = 0;

};


#endif
