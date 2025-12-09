#ifndef _EspeceBestiole_
#define _EspeceBestiole_

#include "config.h"
#include "UImg.h"
#include "Comportement.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Milieu;
class Bestiole;

class EspeceBestiole
{

protected :
   static int        next;
   static bool       configInitialized;

public :
   static double     CLONAGE_PROP;

protected :
   int               identite;
   double            cumulX, cumulY;
   double            vitesse;
   double            orientation;
   int               x, y;
   T               * couleur;

public :        
   EspeceBestiole();                                
   EspeceBestiole(const EspeceBestiole& other);
   virtual ~EspeceBestiole( void ) ;
   
   void initFromConfig();
   int getId() const { return identite; }
   
   virtual void action( Milieu & monMilieu ) = 0;
   virtual void draw( UImg & support ) = 0;
   virtual const std::vector<EspeceBestiole*> detecteBestioles(const std::vector<EspeceBestiole*>& listeBestioles) = 0;
   
   void initCoords( int xLim, int yLim );
   virtual bool idDed() const  = 0;

   void bouge( int xLim, int yLim );

   virtual bool isInCollisionWith( const EspeceBestiole & b ) const ;
   virtual void CollisionEffect()  = 0;
   virtual EspeceBestiole* clone() const = 0;

   friend bool operator==( const EspeceBestiole & b1, const EspeceBestiole & b2 );


   // Getters et Setters
   int getX() const { return x; };
   int getY() const { return y; }
   virtual double getVitesse() const { return vitesse; }
   virtual void setVitesse(double newVitesse) { vitesse = newVitesse; }
   virtual double getOrientation() const { return orientation; };
   virtual void setOrientation(double newOrientation) { orientation = newOrientation; }
   virtual Comportement* getComportement() const { return nullptr; }
   virtual double getCamouflage() const { return 0; };
   virtual double getAffSize() const = 0 ;

};

#endif