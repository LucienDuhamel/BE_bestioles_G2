#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "EspeceBestiole.h"
#include "EspeceBestioleFactory.h"
#include "Comportement.h"
#include <iostream>
#include <vector>

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];
   static const double     TAUX_DE_NAISSANCES_SPONTANE;
   
   int                     width, height;
   std::vector<EspeceBestiole*>   listeEspeceBestioles;
   std::vector<Comportement*> ListComportements;
   EspeceBestioleFactory* bestioleFactory;


public :
   Milieu( int _width, int _height );
   ~Milieu( void );
   void initConfig(int nbEspeces);
   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );
   std::vector<EspeceBestiole*> getListeEspeceBestioles() const {return listeEspeceBestioles;};
   void addMember( EspeceBestiole* b ) { listeEspeceBestioles.push_back(b); listeEspeceBestioles.back()->initCoords(width, height); }
   void addMember() {addMember(bestioleFactory->creerEspeceBestiole()); }
   int nbVoisins( const EspeceBestiole& b );
   void removeMember( EspeceBestiole* b );
   void removeDeds();
   void detecteCollisions();

   

};


#endif
