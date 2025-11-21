#include "Bestiole.h"

#include "Milieu.h"

#include "Bestiole.h"
#include "ICapteur.h"
#include "IAccessoire.h"
#include "Yeux.h"
#include "Oreilles.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Camouflage.h"


#include <cstdlib>
#include <cmath>
#include <unordered_set>


const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;

int               Bestiole::next = 0;




Bestiole::Bestiole( void )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;
   camouflage = 0.0;
   resistance = 0.0;

   couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );


}


Bestiole::Bestiole( const Bestiole & b )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par copie" << endl;

   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   vitesse = b.vitesse;
   camouflage = b.camouflage;
   resistance = b.resistance;
   couleur = new T[ 3 ];
      if (b.couleur) {
         memcpy( couleur, b.couleur, 3*sizeof(T) );
      } else {
         couleur[0] = couleur[1] = couleur[2] = 0;
      }

   // Clone capteurs and accessoires for a deep copy (raw pointers)
   for ( const auto & capteur : b.listeCapteur ) {
      if ( capteur ) listeCapteur.push_back( capteur->clone() );
   }
   for ( const auto & accessoire : b.listeAccessoire ) {
      if ( accessoire ) listeAccessoire.push_back( accessoire->clone() );
   }

}


Bestiole::~Bestiole( void )
{

   delete[] couleur;

   // delete owned raw pointers
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


void Bestiole::initCoords( int xLim, int yLim )
{

   x = rand() % xLim;
   y = rand() % yLim;

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


void Bestiole::action( Milieu & monMilieu )
{

   bouge( monMilieu.getWidth(), monMilieu.getHeight() );

}


void Bestiole::draw( UImg & support )
{

   int            xt = x + static_cast<int>( cos( orientation )*AFF_SIZE );
   int            yt = y + static_cast<int>( -sin( orientation )*AFF_SIZE );

   if ( couleur ) {
      support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
      support.draw_circle( xt, yt, AFF_SIZE/2., couleur );
   } else {
      T defaultColor[3] = { (T)0, (T)0, (T)0 };
      support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., defaultColor );
      support.draw_circle( xt, yt, AFF_SIZE/2., defaultColor );
   }

   // Draw all accessories 
   for (const auto& accessoire : listeAccessoire) {
      if (accessoire) {
         accessoire->draw(support, this);
      }
   }

   // Draw all sensors (pass the current bestiole so markers follow)
   for (const auto& capteur : listeCapteur) {
      if (capteur) {
         capteur->draw(support, this);
      }
   }

}


bool operator==( const Bestiole & b1, const Bestiole & b2 )
{

   return ( b1.identite == b2.identite );

}


std::vector<Bestiole*> Bestiole::jeTeVois(std::vector<Bestiole*> const& listeBestioles) const
{
    std::vector<Bestiole*> resultat;

    // Si aucun capteur, retourne vide
    if (listeCapteur.empty())
        return resultat;

    // Parcours de tous les capteurs de la bestiole
    for (ICapteur* capteur : this->listeCapteur) {
        if (!capteur) continue;

        // detecter attend (liste, Bestiole*)
        std::vector<Bestiole*> ListeBestiolesdetectees = capteur->detecter(listeBestioles, const_cast<Bestiole*>(this));

        // Vérifie les doublons
        for (Bestiole* bestioleDetectee : ListeBestiolesdetectees) {

            // Vérifie si la bestiole est déjà dans resultat
            bool dejaPresent = false;
            for (Bestiole* b : resultat) {
                if (b == bestioleDetectee) {
                    dejaPresent = true;
                    break;
                }
            }

            // Ajoute seulement si pas trouvée
            if (!dejaPresent) {
                resultat.push_back(bestioleDetectee);
            }
        }
    }
    return resultat;
}





int Bestiole::getX() {
    return this->x;
}
int Bestiole::getY() {
    return this->y;
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

int Bestiole::getId() const {
   return identite;
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
   if (accessoire) {
      listeAccessoire.push_back(accessoire);
   }
}