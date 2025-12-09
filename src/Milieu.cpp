#include "Milieu.h"
#include "ComportementGregaire.h"
#include "ComportementKamikaze.h"
#include "ComportementPeureux.h"
#include "ComportementPersoMultiples.h"
#include "ComportementPrevoyant.h"
#include "BestioleFactory.h"
#include "IAccessoire.h"
#include "Bestiole.h"
#include "utils.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };
double  Milieu::PROP_GREGAIRE = 0.0;
double  Milieu::PROP_KAMIKAZE = 0.0;
double  Milieu::PROP_PEUREUX = 0.0;
double  Milieu::PROP_PREVOYANT = 0.0;
double  Milieu::PROP_MULTIPLES = 0.0;
double  Milieu::TAUX_DE_NAISSANCES_SPONTANEE = 0.0;
bool    Milieu::configInitialized = false;


Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{

   // Attention l'ordre d'ajout des comportements détermine leur indice dans la factory
   listeComportements.push_back(ComportementGregaire::getInstance());
   listeComportements.push_back(ComportementKamikaze::getInstance());
   listeComportements.push_back(new ComportementPeureux());
   listeComportements.push_back(ComportementPrevoyant::getInstance());
   listeComportements.push_back(new ComportementPersoMultiples(listeComportements));
   
   if(!configInitialized) {
      this->initFromConfig();
      configInitialized = true;
   }
   std::vector<double> proportions = {PROP_GREGAIRE, PROP_KAMIKAZE, PROP_PEUREUX, PROP_PREVOYANT, PROP_MULTIPLES};
   bestioleFactory = new BestioleFactory(listeComportements, proportions);
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

    // Supprime tous les comportements (Version Main : indispensable pour éviter les fuites)
    for (auto* c : listeComportements) {
        delete c;
    }
    listeComportements.clear();

    // Supprime la factory si elle a été créée dynamiquement
    delete bestioleFactory;
   cout << "dest Milieu" << endl;

}


void Milieu::initConfig(int nbEspeces)
{  
   kill_all();
   for ( int i = 0; i <= nbEspeces; ++i )
      addMember();
}

void Milieu::initFromConfig() {
   // Initialisation du taux de naissances spontanées depuis le fichier de config
   PROP_GREGAIRE = Config::getInstance().getDouble("PROP_GREGAIRE", 0.2);
   PROP_KAMIKAZE = Config::getInstance().getDouble("PROP_KAMIKAZE", 0.2);
   PROP_PEUREUX = Config::getInstance().getDouble("PROP_PEUREUX", 0.2);
   PROP_PREVOYANT = Config::getInstance().getDouble("PROP_PREVOYANT", 0.2);
   PROP_MULTIPLES = Config::getInstance().getDouble("PROP_MULTIPLES", 0.2);

   if(PROP_GREGAIRE + PROP_KAMIKAZE + PROP_PEUREUX + PROP_PREVOYANT + PROP_MULTIPLES != 1){
      std::cout<<"Les proportions de types de bestioles doivent faire 1 en les sommant !!"<<std::endl;
   }
   TAUX_DE_NAISSANCES_SPONTANEE = Config::getInstance().getDouble("TAUX_DE_NAISSANCES_SPONTANE", 0.01);
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
      if(randomBetween(0.0,1.0) <= listeEspeceBestioles[i]->CLONAGE_PROP)
         //listeEspeceBestioles.push_back(listeEspeceBestioles[i]->clone());
         addMember(listeEspeceBestioles[i]->clone());

   // Naissance spontanement
   if(randomBetween(0.0,1.0) <= TAUX_DE_NAISSANCES_SPONTANEE)
      addMember();
   
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
   {

      (*it)->action( *this );
      (*it)->draw( *this );

   } // for

}

void Milieu::removeMember(  EspeceBestiole* b )
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

// Dans code_v1_2/src/Milieu.cpp

void Milieu::removeDeds()
{
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
   {
      if((*it)->idDed())
      {
         Bestiole* b = dynamic_cast<Bestiole*>(*it);
         if (b) {
             StatMortalite stat;
             stat.ageAuDeces = b->getAge(); 
             
             // Récupération des accessoires
             for (auto acc : b->getListeAccessoire()) {
                 stat.accessoires.push_back(acc->getLabel());
             }
             
             registreDeces.push_back(stat);
         }

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


void Milieu::kill_all()
{
   for ( std::vector<EspeceBestiole*>::iterator it = listeEspeceBestioles.begin() ; it != listeEspeceBestioles.end() ; ++it )
      delete *it;

   listeEspeceBestioles.clear();
}