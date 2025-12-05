#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"
#include "config.h"
#include <iostream>
#include "Comportement.h"
#include "Milieu.h"
#include "EspeceBestiole.h"
#include <memory>
#include <vector>

using namespace std;

class Milieu;
class ICapteur;
class IAccessoire;

class Bestiole : public EspeceBestiole
{

private :
   static double     MAX_VITESSE;
   static int        MAX_AGE;

   

private :
   int               age;
   int               age_Lim;
   double deathProb;
   bool Killed;
   double            camouflage;
   double            resistance;

   Comportement* comportement;

   std::vector<ICapteur*> listeCapteur;
   std::vector<IAccessoire*> listeAccessoire;

   

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

   const std::vector<EspeceBestiole*> detecteBestioles(const std::vector<EspeceBestiole*>& listeBestioles) override;

   EspeceBestiole* clone() const override;

   // Pour les bestioles a comportements multiples
   double getCamouflage();
   double getResistance();
   double getCamouflage() const override {return camouflage; }
   const std::vector<ICapteur*>& getListeCapteur() const;
   const std::vector<IAccessoire*>& getListeAccessoire() const;

   void setCamouflage(double camouflage);
   void setResistance(double resistance);

   void addCapteur(ICapteur* capteur);
   void addAccessoire(IAccessoire* accessoire);

};


#endif
