#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include <iostream>
#include <memory>
#include <vector>

class Milieu;
class ICapteur;
class IAccessoire;


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

   double            camouflage;
   double            resistance;

public:
   std::vector<ICapteur*> listeCapteur;
   std::vector<IAccessoire*> listeAccessoire;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   std::vector<Bestiole*> jeTeVois(const std::vector<Bestiole*>& listeBestioles) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );


   int getX();
   int getY();
   double getVitesse();
   double getCamouflage();
   double getResistance();
   double getOrientation();
   const std::vector<ICapteur*>& getListeCapteur() const;

   void setVitesse(double vitesse);
   void setCamouflage(double camouflage);
   void setResistance(double resistance);

   void addCapteur(ICapteur* capteur);
   void addAccessoire(IAccessoire* accessoire);
   int getId() const;
};


#endif
