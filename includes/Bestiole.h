#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"
#include "config.h"
#include <iostream>
#include "Comportement.h"
#include "Milieu.h"
#include "EspeceBestiole.h"

using namespace std;



class Bestiole : public EspeceBestiole
{

private :
   static double     MAX_VITESSE;
   static int        MAX_AGE;

   // Pour les bestioles a comportements multiples
   static double     MAX_PROBA_CHANGEMENT_COMPORTEMENT;

private :
   int               age;
   int               age_Lim;
   double deathProb;
   bool Killed;
   Comportement* comportement;

   // Pour les bestioles a comportements multiples
   double probaChangementComportement;
   Comportement* comportementApparent;

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );

   void initFromConfig();
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

   // Pour les bestioles a comportements multiples
   double getProbaChangementComportement() const { return probaChangementComportement; };
   Comportement* getComportementApparent() const { return comportementApparent; };
   void setComportementApparent(Comportement* newComportementApparent) { comportementApparent = newComportementApparent; }; 

};


#endif
