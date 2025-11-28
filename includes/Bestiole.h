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
   int               age;
   int               age_Lim;
   double deathProb;
   bool Killed;


   Comportement* comportement;

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );
                                                    // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu ) override;
   void draw( UImg & support ) override;


   void setCouleur(T   * couleur);
   void setComportement(   Comportement* comportement);
   bool idDed() const override;

   void CollisionEffect() override;
   double getDeathProb() const;

   bool jeTeVois( const EspeceBestiole & b ) const override;
   const std::vector<EspeceBestiole*> detecteBestioles(const std::vector<EspeceBestiole*>& listeBestioles);

   EspeceBestiole* clone() const override;

};


#endif
