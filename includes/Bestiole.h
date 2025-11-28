#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

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
   double            camouflage;
   double            resistance;

   Comportement* comportement;
public:
   std::vector<ICapteur*> listeCapteur;
   std::vector<IAccessoire*> listeAccessoire;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );
                                                    // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu ) override;
   void draw( UImg & support ) override;
   void setCouleur(T   * couleur);
   bool jeTeVois( const EspeceBestiole & b ) const override;
   void setComportement(   Comportement* comportement);
   bool idDed() const override;

   void CollisionEffect() override;
   double getDeathProb() const;

   EspeceBestiole* clone() const override;

   double getVitesse();
   double getCamouflage();
   double getResistance();
   double getOrientation();
   const std::vector<ICapteur*>& getListeCapteur() const;
   const std::vector<IAccessoire*>& getListeAccessoire() const;

   void setVitesse(double vitesse);
   void setCamouflage(double camouflage);
   void setResistance(double resistance);

   void addCapteur(ICapteur* capteur);
   void addAccessoire(IAccessoire* accessoire);

};


#endif
