
#include "EspeceBestiole.h"

const double      EspeceBestiole::AFF_SIZE = 8.;
const double      EspeceBestiole::LIMITE_VUE = 30.;
int               EspeceBestiole::next = 0;
const double      EspeceBestiole::CLONAGE_PROP = 0.01;

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
