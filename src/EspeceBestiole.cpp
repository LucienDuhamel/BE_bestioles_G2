#include "EspeceBestiole.h"
#include "Milieu.h"

const double      EspeceBestiole::AFF_SIZE = 8.;
const double      EspeceBestiole::LIMITE_VUE = 100.;
int               EspeceBestiole::next = 0;
const double      EspeceBestiole::CLONAGE_PROP = 0.1;

EspeceBestiole::EspeceBestiole()
{
    // Nouvel identifiant
    identite = ++next;

    // Copier les coordonnées
    x = 0;
    y = 0;

    couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

}

EspeceBestiole::EspeceBestiole(const EspeceBestiole& other)
{
    // Nouvel identifiant
    identite = ++next;

    // Copier les coordonnées
    x = other.x;
    y = other.y;

    // Copier la couleur profondément
    couleur = new T[3];
    memcpy(couleur, other.couleur, 3 * sizeof(T));
}

EspeceBestiole::~EspeceBestiole( void )
{

   delete[] couleur;

   cout << "dest EspeceBestiole" << endl;

}

void EspeceBestiole::action( Milieu & monMilieu )
{
   if(idDed())
   {
      couleur[ 0 ] = 0;
      couleur[ 1 ] = 0;
      couleur[ 2 ] = 0;
      return;
   }

   bouge( monMilieu.getWidth(), monMilieu.getHeight());
}

void EspeceBestiole::bouge( int xLim, int yLim )
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

void EspeceBestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

}

bool EspeceBestiole::isInCollisionWith( const EspeceBestiole & b ) const
{
   // TO do
    double dx = x - b.x;
    double dy = y - b.y;
    double dist2 = dx*dx + dy*dy;

    double minDist = 2*AFF_SIZE; // à adapter selon ton attribut réel

    return dist2 < (minDist * minDist);
}


void EspeceBestiole::initCoords( int xLim, int yLim )
{

   x = rand() % xLim;
   y = rand() % yLim;

}



bool operator==( const EspeceBestiole & b1, const EspeceBestiole & b2 )
{

   return ( b1.identite == b2.identite );

}
