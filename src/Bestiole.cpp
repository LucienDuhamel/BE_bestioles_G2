#include "Bestiole.h"

#include "Milieu.h"
#include "utils.h"

#include <cstdlib>
#include <cmath>


const double      Bestiole::MAX_VITESSE = 10.;

const int         Bestiole::MAX_AGE = 1000;


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

}



Bestiole::~Bestiole( void )
{


   cout << "dest Bestiole -> " ;

}

void Bestiole::setComportement(   Comportement* leComportement)
{

   comportement = leComportement;

}

void Bestiole::setCouleur(T   * coul)
{
   memcpy(couleur, coul, 3 * sizeof(T));
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


   dist = calcDistance( *this, b );
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
   comportement->reagit(*this, monMilieu.getListeEspeceBestioles() );
   bouge( monMilieu.getWidth(), monMilieu.getHeight());

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


const std::vector<EspeceBestiole*> Bestiole::detecteBestioles( const std::vector<EspeceBestiole*>& listeBestioles)
{  
   std::vector<EspeceBestiole*> listeBestiolesDetectees;

   for (EspeceBestiole* other : listeBestioles) 
   {
      if (other != nullptr && other != this && jeTeVois(*other))
      {
         listeBestiolesDetectees.push_back(other);
      }
   }

   return listeBestiolesDetectees;
}
