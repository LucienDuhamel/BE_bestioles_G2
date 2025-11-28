#include "Bestiole.h"
#include "ICapteur.h"
#include "IAccessoire.h"
#include "Yeux.h"
#include "Oreilles.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Camouflage.h"

#include "Milieu.h"

#include <cstdlib>
#include <cmath>


const double      Bestiole::MAX_VITESSE = 10.;

const int         Bestiole::MAX_AGE = 100;


Bestiole::Bestiole( void )
{

   //identite = ++next;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   age_Lim = static_cast<double>( rand() )/RAND_MAX*MAX_AGE;
   age = 0;
   Killed = false;
   deathProb = static_cast<double>( rand() )/RAND_MAX;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;
   camouflage = 0.0;
   resistance = 0.0;
   
}


Bestiole::Bestiole( const Bestiole & b ) : EspeceBestiole(b)
{


   cout << "const Bestiole (" << identite << ") par copie : from "<< b.identite << endl;

   age_Lim = b.age_Lim;
   age = b.age;
   Killed = b.Killed;
   deathProb = b.deathProb;
   cumulX = cumulY = 0.;
   comportement = b.comportement;
   orientation = b.orientation;
   vitesse = b.vitesse;
   camouflage = b.camouflage;
   resistance = b.resistance;
   //Clone les capteurs et accessoires avec une deep copy
   for ( const auto & capteur : b.listeCapteur ) {
      if ( capteur ) listeCapteur.push_back( capteur->clone() );
   }
   for ( const auto & accessoire : b.listeAccessoire ) {
      if ( accessoire ) listeAccessoire.push_back( accessoire->clone() );
   }
}



Bestiole::~Bestiole( void )
{
   // delete les pointeurs des capteurs et accessoires
   for (auto p : listeCapteur) {
      delete p;
   }
   listeCapteur.clear();
   for (auto p : listeAccessoire) {
      delete p;
   }
   listeAccessoire.clear();

   cout << "dest Bestiole" << endl;

}

void Bestiole::setComportement(   Comportement* Lecomportement)
{

   comportement = Lecomportement;

}

void Bestiole::setCouleur(T   * coul)
{
   memcpy(couleur, coul, 3 * sizeof(T));
}
void Bestiole::bouge( int xLim, int yLim )
{

   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;


   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;
   ny = y + dy + cy;

   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );
      cumulX += nx - x;
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }

}

double Bestiole::getDeathProb() const
{
   return deathProb;
}


void Bestiole::CollisionEffect()
{
   // TO Do

   // Sinon elle rebondit = demi-tour
    orientation += M_PI;
    double r = (double)rand() / RAND_MAX;

    if (r < getDeathProb())
    {
        Killed = true ;      // marque la bestiole comme morte
        return;
    }

    
}

bool Bestiole::jeTeVois( const EspeceBestiole & b ) const
{

   double         dist;


   dist = std::sqrt( (x-b.getX())*(x-b.getX()) + (y-b.getY())*(y-b.getY()) );
   return ( dist <= LIMITE_VUE );

}
void Bestiole::action( Milieu & monMilieu )
{
   if(idDed())
   {
      couleur[ 0 ] = 0;
      couleur[ 1 ] = 0;
      couleur[ 2 ] = 0;
      return;
   }
   age++;
   comportement->bouge(*this, monMilieu.getListeEspeceBestioles() );
   bouge( monMilieu.getWidth(), monMilieu.getHeight() );

}


void Bestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

}

bool Bestiole::idDed() const
{
   if(age>=age_Lim)
   {
      cout<< "(" << identite << ") age limit reached " ;
   }
   
   if (Killed)
   {
      cout<< "(" << identite << ")  killed           " ;
   }
   return age>=age_Lim || Killed ;
}



EspeceBestiole* Bestiole::clone() const
{
    return new Bestiole(*this);
}


double Bestiole::getVitesse() {
    return this->vitesse;
}
double Bestiole::getCamouflage() {
    return this->camouflage;
}
double Bestiole::getResistance() {
    return this->resistance;
}
double Bestiole::getOrientation() {
    return this->orientation;
}
const std::vector<ICapteur*>& Bestiole::getListeCapteur() const {
   return this->listeCapteur;
}
const std::vector<IAccessoire*>& Bestiole::getListeAccessoire() const {
   return this->listeAccessoire;
}



void Bestiole::setVitesse(double vitesse) {
   this->vitesse = vitesse;
}
void Bestiole::setCamouflage(double camouflage) {
   this->camouflage = camouflage;
}
void Bestiole::setResistance(double resistance) {
   this->resistance = resistance;
}
void Bestiole::addCapteur(ICapteur* capteur) {
   if (capteur) {
      listeCapteur.push_back(capteur);
   }
}

void Bestiole::addAccessoire(IAccessoire* accessoire) {
   if (!accessoire) return;

   // Bestiole prend possession de l'accessoire
   listeAccessoire.push_back(accessoire);

   // Applique immédiatement les effets connus selon le type d'accessoire
   if ( Carapace* c = dynamic_cast<Carapace*>(accessoire) ) {
      c->setVitesseCarapace(this);
      c->setResistanceCarapace(this);
   }
   else if ( Nageoires* n = dynamic_cast<Nageoires*>(accessoire) ) {
      n->setVitesseNageoires(this);
   }
   else if ( Camouflage* cam = dynamic_cast<Camouflage*>(accessoire) ) {
      cam->setCamouflage(this);
   }
}