#ifndef _Comportement_
#define _Comportement_

#include "config.h"
#include "UImg.h"

#include <iostream>
#include <vector>
#include <string> // Nécessaire pour getName()

class Bestiole;
class EspeceBestiole;

class Comportement
{

public :
   
   virtual ~Comportement( )= default;

   virtual T * getCouleur() const = 0;

   // Version Main (sans const) pour compatibilité avec les classes filles
   virtual void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) = 0;

   // Version Main (nécessaire pour la copie de Bestiole)
   virtual Comportement* clone() const = 0;

   // Votre ajout (nécessaire pour l'analyse de simulation)
   virtual std::string getName() const = 0;
};


#endif