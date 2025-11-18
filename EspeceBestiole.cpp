
#include "EspeceBestiole.h"

const double      EspeceBestiole::AFF_SIZE = 8.;
const double      EspeceBestiole::LIMITE_VUE = 30.;
int               EspeceBestiole::next = 0;




EspeceBestiole::~EspeceBestiole( void )
{

   delete[] couleur;

   cout << "dest EspeceBestiole" << endl;

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

bool EspeceBestiole::jeTeVois( const EspeceBestiole & b ) const
{

   double         dist;


   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( dist <= LIMITE_VUE );

}

bool operator==( const EspeceBestiole & b1, const EspeceBestiole & b2 )
{

   return ( b1.identite == b2.identite );

}
