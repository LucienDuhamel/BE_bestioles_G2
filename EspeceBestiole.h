#ifndef _EspeceBestiole_
#define _EspeceBestiole_


#include "UImg.h"

#include <iostream>

using namespace std;


class Milieu;

class EspeceBestiole
{

protected :
   static const double     AFF_SIZE;
   static const double     LIMITE_VUE;
   static int              next;

protected :
   int               identite;

   int               x, y;
   T               * couleur;


public :                                        
   virtual ~EspeceBestiole( void ) ;
   virtual void action( Milieu & monMilieu ) = 0;
   virtual void draw( UImg & support ) = 0;

   virtual bool jeTeVois( const EspeceBestiole & b ) const ;
   void initCoords( int xLim, int yLim );
   virtual bool idDed() const  = 0;

   virtual bool isInCollisionWith( const EspeceBestiole & b ) const ;
   virtual void CollisionEffect()  = 0;

   friend bool operator==( const EspeceBestiole & b1, const EspeceBestiole & b2 );

};


#endif
