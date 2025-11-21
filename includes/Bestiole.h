#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"
#include "utils.h"
#include "ComportementBestiole.h"

#include <iostream>

using namespace std;


class Milieu;


class Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;

   static int              next;

private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;

   T               * couleur;

   const ComportementBestiole& comportement;

private :
   void bouge( int xLim, int yLim, auto& listeBestioles );

public :                                           // Forme canonique :
   Bestiole( const ComportementBestiole& comportement );  // Constructeur par defaut (ajout comportement)
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole& b ) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

   const std::vector<std::unique_ptr<Bestiole>> detecteBestioles(std::vector<std::unique_ptr<Bestiole>> listeBestioles);

   double getVitesse() const { return vitesse; };
   void setVitesse(double newVitesse) { vitesse = newVitesse; }

   double getX() const { return x; };
   double getY() const { return y; };  

   double getOrientation() const { return orientation; };
   void setOrientation(double newOrientation) { orientation = newOrientation; }

};


#endif
