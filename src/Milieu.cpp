#include "Milieu.h"
#include "ComportementGregaire.h"
#include "ComportementKamikaze.h"
#include "ComportementPeureux.h"
#include "ComportementPersoMultiples.h"
#include "ComportementPrevoyant.h"
#include "BestioleFactory.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>
const T    Milieu::white[] = { (T)255, (T)255, (T)255 };
const double  Milieu::TAUX_DE_NAISSANCES_SPONTANE = 0.4;//static_cast<double>( rand() ) / RAND_MAX;

Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{
   ListeComportements.push_back(ComportementGregaire::getInstance());
   ListeComportements.push_back(ComportementKamikaze::getInstance());
   ListeComportements.push_back(ComportementPeureux::getInstance());
   ListeComportements.push_back(ComportementPrevoyant::getInstance());

   ListeComportements.push_back(ComportementPersoMultiples::getInstance(ListeComportements));
   
   std::vector<double> proportions = {0.2, 0.1, 0.1, 0.3, 0.3};
   bestioleFactory = new BestioleFactory(ListeComportements, proportions);
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
    for (auto* c : ListeComportements) {
        delete c;
    }
    ListeComportements.clear();

    // Supprime la factory si elle a été créée dynamiquement
    delete bestioleFactory;
   cout << "dest Milieu" << endl;

}

void Milieu::initConfig(int nbEspeces)
{
   for ( int i = 1; i <= nbEspeces; ++i )
      addMember();
}


void Milieu::step( void )
{

   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );

   // Collisions
   detecteCollisions();
   // Mort des bestioles
   removeDeds();
   

   // clonage spontanement

   
   for ( int i= listeEspeceBestioles.size()-1; i >=0 ; i-- )
      if((double)std::rand() / RAND_MAX <= listeEspeceBestioles[i]->CLONAGE_PROP)
         //listeEspeceBestioles.push_back(listeEspeceBestioles[i]->clone());
         addMember(listeEspeceBestioles[i]->clone());

   // Naissance spontanement
   if((double)std::rand() / RAND_MAX <= TAUX_DE_NAISSANCES_SPONTANE)
      addMember();
   
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
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it)
      for ( std::vector<EspeceBestiole*>::iterator itt = listeEspeceBestioles.begin() ; itt != listeEspeceBestioles.end() ; ++itt )
         if(it!=itt && (*it)->isInCollisionWith( *(*itt) ))
         {
            (*it)->CollisionEffect();
            break;
         }
}
