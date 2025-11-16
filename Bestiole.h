#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include <iostream>
#include "Comportement.h"

using namespace std;


class Milieu;

class Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;
   static const int        MAX_AGE;
   static int              next;

private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   int               age;
   int               age_Lim;
   double deathProb;
   T               * couleur;
   bool Killed;


   Comportement* comportement;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );
   void setComportement(   Comportement* comportement);
   bool idDed() const;

   bool isInCollisionWith( const Bestiole & b ) const;
   void CollisionEffect();
   double getDeathProb() const;

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

};


#endif
