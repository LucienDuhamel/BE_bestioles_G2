#include "Bestiole.h"
#include "ICapteur.h"
#include "IAccessoire.h"
#include "Yeux.h"
#include "Oreilles.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Camouflage.h"

#include "Milieu.h"
#include "utils.h"

#include <cstdlib>
#include <cmath>

#include <iostream>

int         Bestiole::MAX_AGE = 0;
double      Bestiole::MAX_VITESSE = 0.0;
double      Bestiole::MAX_PROBA_CHANGEMENT_COMPORTEMENT = 0.0;

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

   // Initialisation des parametres statiques depuis le fichier de config
   if( MAX_AGE == 0 || MAX_VITESSE == 0.0 )
   {
      initFromConfig();
   }

   probaChangementComportement = static_cast<double>( randomBetween(0.0, MAX_PROBA_CHANGEMENT_COMPORTEMENT) );
   
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

   // Bestioles comportements multiples
   probaChangementComportement = b.probaChangementComportement;
   comportementApparent = b.comportementApparent;

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

// Initialisation des parametres statiques depuis le fichier de config (valeurs par defaut si absentes)
void Bestiole::initFromConfig() {
    MAX_AGE = Config::getInstance().getInt("MAX_AGE", 1000);
    MAX_VITESSE = Config::getInstance().getDouble("MAX_VITESSE", 5.0);
    MAX_PROBA_CHANGEMENT_COMPORTEMENT = Config::getInstance().getDouble("MAX_PROBA_CHANGEMENT_COMPORTEMENT", 0.05);
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

std::vector<Bestiole*> Bestiole::detecteBestioles(std::vector<Bestiole*> const& listeBestioles) const
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

   //Dessin des Accessoires
    for (auto accessoire : listeAccessoire) {
        accessoire->draw(support, this);
    }

    // Dessin des Capteurs 
    for (auto capteur : listeCapteur) {
        capteur->draw(support, this);
    }

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
double Bestiole::getCamouflage() {
    return this->camouflage;
}
double Bestiole::getResistance() {
    return this->resistance;
}
const std::vector<ICapteur*>& Bestiole::getListeCapteur() const {
   return this->listeCapteur;
}
const std::vector<IAccessoire*>& Bestiole::getListeAccessoire() const {
   return this->listeAccessoire;
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
