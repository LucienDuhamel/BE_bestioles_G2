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

// Initialisation des statiques
double      Bestiole::AFF_SIZE = -1.0;
int         Bestiole::MAX_AGE = -1.0;
double      Bestiole::MAX_VITESSE = -1.0;
bool        Bestiole::configInitialized = false;

Bestiole::Bestiole( void )
{  
   // Pour le débogage
   // cout << "const Bestiole (" << identite << ") par defaut" << endl;

   // Utilisation de la configuration globale
   if (!configInitialized) {
      initFromConfig();
      configInitialized = true;
   }

   age_Lim = randomBetween(0.0,1.0)*MAX_AGE;
   age = 0;
   Killed = false;
   deathProb = randomBetween(0.0,1.0);
   cumulX = cumulY = 0.;
   
   orientation = randomBetween(0.0,1.0)*2.*M_PI;
   vitesse = randomBetween(0.0,1.0)*MAX_VITESSE;
   vIni = vitesse;
   
   camouflage = 0.0;
   resistance = 1.0;
}

Bestiole::Bestiole( const Bestiole & b ) : EspeceBestiole(b)
{  
   // Pour le débogage
   // cout << " (" << identite << ") par copie : from "<< b.identite << endl;

   age_Lim = b.age_Lim;
   age = b.age;
   Killed = b.Killed;
   deathProb = b.deathProb;
   cumulX = cumulY = 0.;
   
   // Clone le comportement (Deep copy)
   setComportement(b.comportement->clone());
   
   orientation = b.orientation;
   vitesse = b.vitesse;
   vIni = b.vIni;

   camouflage = b.camouflage;
   resistance = b.resistance;

   // Clone les capteurs et accessoires avec une deep copy 
   for ( const auto & capteur : b.listeCapteur ) 
      addCapteur( capteur->clone() );

   for ( const auto & accessoire : b.listeAccessoire )
   {
      if ( accessoire ) listeAccessoire.push_back( accessoire->clone() );
   }
}

Bestiole::~Bestiole( void )
{
   // Nettoyage propre de la mémoire
   for (auto p : listeCapteur) {
      delete p;
   }
   listeCapteur.clear();
   
   for (auto p : listeAccessoire) {
      delete p;
   }
   listeAccessoire.clear();

   // Gestion fine du pointeur de comportement
   Comportement* test = comportement->clone();
   if(test != comportement) 
   {
      delete test;
      delete comportement;
   }
   // Pour le débogage
   // cout << "dest Bestiole" << endl;
}

// Initialisation des parametres statiques depuis le fichier de config
void Bestiole::initFromConfig() {
    AFF_SIZE = Config::getInstance().getDouble("AFF_SIZE", 8.0);
    MAX_AGE = Config::getInstance().getInt("MAX_AGE", 1000);
    MAX_VITESSE = Config::getInstance().getDouble("MAX_VITESSE", 5.0);
}

void Bestiole::setComportement( Comportement* leComportement)
{
   comportement = leComportement;
   setCouleur(comportement->getCouleur());
}

void Bestiole::setCouleur(T * coul)
{
   memcpy(couleur, coul, 3 * sizeof(T));
}

double Bestiole::getDeathProb() const
{
   return deathProb/resistance;
}

void Bestiole::CollisionEffect()
{
    double r = randomBetween(0.0,1.0);

    if (r < getDeathProb())
    {
        Killed = true ;      // marque la bestiole comme morte
        return;
    }

    // Déviation aléatoire pour éviter de rester bloqué
    double deviation = randomBetween(-M_PI/2, M_PI/2);
    orientation += deviation;
    
    // Normaliser l'orientation entre 0 et 2*PI
    while (orientation < 0) orientation += 2*M_PI;
    while (orientation >= 2*M_PI) orientation -= 2*M_PI;
    
    // Petit recul pour séparer les bestioles
    x -= static_cast<int>(cos(orientation) * vitesse * 2);
    y += static_cast<int>(sin(orientation) * vitesse * 2);
}

const std::vector<EspeceBestiole*> Bestiole::detecteBestioles(const std::vector<EspeceBestiole*>& listeBestioles)
{
    std::vector<EspeceBestiole*> resultat;

    // Si aucun capteur, retourne vide
    if (listeCapteur.empty())
        return resultat;

    // Parcours de tous les capteurs de la bestiole
    for (ICapteur* capteur : this->listeCapteur) {
        if (!capteur) continue;

        // Appel au capteur
        std::vector<EspeceBestiole*> ListeBestiolesdetectees = capteur->detecter(listeBestioles, this);

        // Vérifie les doublons
        for (EspeceBestiole* bestioleDetectee : ListeBestiolesdetectees) {
            bool dejaPresent = false;
            for (EspeceBestiole* b : resultat) {
                if (b == bestioleDetectee) {
                    dejaPresent = true;
                    break;
                }
            }
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
   
   // Utilise la méthode bouge de la classe mère (EspeceBestiole)
   bouge( monMilieu.getWidth(), monMilieu.getHeight());
}

void Bestiole::draw( UImg & support )
{
   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;

   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

   // Dessin des Accessoires
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
   // Debug info
   // if(age>=age_Lim)
   // {
   //    cout<< "(" << identite << ") age limit reached " ;
   // }
   
   // if (Killed)
   // {
   //    cout<< "(" << identite << ")  killed           " ;
   // }
   return age>=age_Lim || Killed ;
}

EspeceBestiole* Bestiole::clone() const
{
    return new Bestiole(*this);
}

// Getters et Setters pour accessoires

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

   // Applique immédiatement les effets
   accessoire->setParameters(this);
}