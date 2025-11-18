#include "Milieu.h"
#include "ComportementGregaire.h"
#include "ComportementKamikaze.h"
#include "ComportementPeureux.h"
#include "ComportementPersoMultiples.h"
#include "ComportementPrevoyant.h"
#include "BestioleFactory.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{
   ListComportements.push_back(ComportementGregaire::getInstance());
   ListComportements.push_back(ComportementKamikaze::getInstance());
   ListComportements.push_back(ComportementPeureux::getInstance());
   ListComportements.push_back(ComportementPrevoyant::getInstance());
   ListComportements.push_back(ComportementPersoMultiples::getInstance(ListComportements));
   std::vector<double> proportions = {0.2, 0.1, 0.1, 0.3, 0.3};
   bestioleFactory = new BestioleFactory(ListComportements, proportions);
   cout << "const Milieu" << endl;

   std::srand( time(NULL) );

}


Milieu::~Milieu( void )
{
   // Supprime toutes les bestioles
    for (auto* b : listeEspeceBestioles) {
        delete b;
    }
    listeEspeceBestioles.clear();

    // Supprime tous les comportements
    for (auto* c : ListComportements) {
        delete c;
    }
    ListComportements.clear();

    // Supprime la factory si elle a été créée dynamiquement
    delete bestioleFactory;
   cout << "dest Milieu" << endl;

}

void Milieu::initConfig(int nbEspeces)
{
   for ( int i = 1; i <= nbEspeces; ++i )
      addMember( bestioleFactory->creerEspeceBestiole() );
}


void Milieu::step( void )
{

   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   detecteCollisions();
   removeDeds();
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
   {

      (*it)->action( *this );
      (*it)->draw( *this );

   } // for

}


int Milieu::nbVoisins( const EspeceBestiole & b )
{

   int         nb = 0;


   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
      if ( !(b == *(*it)) && b.jeTeVois(*(*it)) )
         ++nb;

   return nb;

}
void Milieu::removeMember(  EspeceBestiole*  b )
{
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
   {
      if((*b)==*(*it))
      {
         delete *it;
         listeEspeceBestioles.erase(it);
         return;
      }

   }
   std::cout<<" SUPPRESSION IMPOSSIBLE : EspeceBestiole n'est pas dans la list "<<std::endl;
}
void Milieu::removeDeds()
{
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
   {
      if((*it)->idDed())
      {
         delete *it;
         listeEspeceBestioles.erase(it--);
      }

   }
}

void Milieu::detecteCollisions()
{
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
   {
      std::vector<EspeceBestiole*>::iterator itt = it;
      for ( itt++ ; itt != listeEspeceBestioles.end() ; ++itt )
      {
         if((*it)->isInCollisionWith( *(*itt) ))
         {
            (*it)->CollisionEffect();
            (*itt)->CollisionEffect();
         }

      }
   }
}