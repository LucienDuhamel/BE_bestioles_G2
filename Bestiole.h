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
   void bouge( int xLim, int yLim );

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

   EspeceBestiole* clone() const override;

   Comportement* getComportement() const override { return comportement; }
   double getorientation() const override { return orientation; }
   double getVitesse() const override { return vitesse; }



};


#endif
