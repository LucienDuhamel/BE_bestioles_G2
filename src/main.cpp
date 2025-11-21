#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "ComportementGregaire.h"
#include "ComportementKamikaze.h"
#include "ComportementPeureux.h"

#include <iostream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 640, 480, 30 );
   ComportementKamikaze comportementKamikaze;
   ComportementGregaire comportementGregaire;
   ComportementPeureux comportementPeureux;



   for ( int i = 1; i <= 7; ++i )
      ecosysteme.getMilieu().addMember( Bestiole(comportementKamikaze) );

   for ( int i = 1; i <= 7; ++i )
      ecosysteme.getMilieu().addMember( Bestiole(comportementGregaire) );

   for ( int i = 1; i <= 7; ++i )
      ecosysteme.getMilieu().addMember( Bestiole(comportementPeureux) );
   ecosysteme.run();


   return 0;

}
