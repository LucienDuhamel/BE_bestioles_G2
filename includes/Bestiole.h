#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include <iostream>
#include "Comportement.h"
#include "Milieu.h"
#include "EspeceBestiole.h"

using namespace std;



class Bestiole : public EspeceBestiole
{

private :
   
   static const double     MAX_VITESSE;
   static const int        MAX_AGE;

private :
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   int               age;
   int               age_Lim;
   double deathProb;
   bool Killed;


   Comportement* comportement;

private :
   void bouge( int xLim, int yLim, Milieu & monMilieu );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );
                                                    // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu ) override;
   void draw( UImg & support ) override;


   void setComportement(   Comportement* comportement);
   bool idDed() const override;

   void CollisionEffect() override;
   double getDeathProb() const;

   bool jeTeVois( const EspeceBestiole & b  ) const ;
   const std::vector<EspeceBestiole*>& detecteBestioles(const std::vector<EspeceBestiole*>& listeBestioles);

   EspeceBestiole* clone() const override;

   double getVitesse() const { return vitesse; };
   void setVitesse(double newVitesse) { vitesse = newVitesse; }

   double getX() const { return x; };
   double getY() const { return y; };  

   double getOrientation() const { return orientation; };
   void setOrientation(double newOrientation) { orientation = newOrientation; }

};


#endif
