#include "Bestiole.h"

#include "Milieu.h"

#include <cstdlib>
#include <cmath>
#define M_PI 3.14


const double      Bestiole::MAX_VITESSE = 10.;

const int         Bestiole::MAX_AGE = 20;


Bestiole::Bestiole( void )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   age_Lim = static_cast<double>( rand() )/RAND_MAX*MAX_AGE;
   age = 0;
   Killed = false;
   deathProb = static_cast<double>( rand() )/RAND_MAX;
   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;

   couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

}


Bestiole::Bestiole( const Bestiole & b )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par copie" << endl;

   age_Lim = b.age_Lim;
   age = 0;
   Killed = b.Killed;
   deathProb = b.deathProb;
   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   vitesse = b.vitesse;
   couleur = new T[ 3 ];
   memcpy( couleur, b.couleur, 3*sizeof(T) );

}


Bestiole::~Bestiole( void )
{


   cout << "dest Bestiole" << endl;

}

void Bestiole::setComportement(   Comportement* Lecomportement)
{

   comportement = Lecomportement;

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
   return age>=age_Lim || Killed ;
}




