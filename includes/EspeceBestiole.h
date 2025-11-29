#ifndef _EspeceBestiole_
#define _EspeceBestiole_

#include "config.h"
#include "UImg.h"

#include <iostream>

using namespace std;


class Milieu;

class EspeceBestiole
{

protected :
   static double     AFF_SIZE;
   static double     LIMITE_VUE;
   static int              next;

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
   virtual void action( Milieu & monMilieu );
   virtual void draw( UImg & support );
   virtual bool jeTeVois( const EspeceBestiole & b ) const = 0 ;
   void initCoords( int xLim, int yLim );
   virtual bool idDed() const  = 0;

   void bouge( int xLim, int yLim );

   virtual bool isInCollisionWith( const EspeceBestiole & b ) const ;
   virtual void CollisionEffect()  = 0;
   virtual EspeceBestiole* clone() const = 0;

   friend bool operator==( const EspeceBestiole & b1, const EspeceBestiole & b2 );

   int getX() const { return x; };
   int getY() const { return y; };

   double getVitesse() const { return vitesse; };
   void setVitesse(double newVitesse) { vitesse = newVitesse; }

   double getOrientation() const { return orientation; };
   void setOrientation(double newOrientation) { orientation = newOrientation; }

};


#endif
