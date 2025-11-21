#ifndef _EspeceBestioleFactory_
#define _EspeceBestioleFactory_


#include "EspeceBestiole.h"


class EspeceBestioleFactory
{

public :
   virtual ~EspeceBestioleFactory( void )= default;

   virtual EspeceBestiole* creerEspeceBestiole() const = 0;

};


#endif
