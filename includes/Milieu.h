#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "config.h"
#include "UImg.h"
#include "EspeceBestiole.h"
#include "EspeceBestioleFactory.h"
#include "Comportement.h"
#include <iostream>
#include <vector>

using namespace std;

// Structure simple pour stocker les données d'un défunt
struct StatMortalite {
    int ageAuDeces;
    std::vector<std::string> accessoires;
};

class Milieu : public UImg
{

private :
   static const T          white[];
   
   // Paramètres de configuration (Architecture Main)
   static double           PROP_GREGAIRE;
   static double           PROP_KAMIKAZE;
   static double           PROP_PEUREUX;
   static double           PROP_PREVOYANT;
   static double           PROP_MULTIPLES;
   static double           TAUX_DE_NAISSANCES_SPONTANEE;
   static bool             configInitialized;
   
   int                     width, height;
   std::vector<EspeceBestiole*>   listeEspeceBestioles;
   std::vector<Comportement*>     listeComportements;
   EspeceBestioleFactory* bestioleFactory;

   std::vector<StatMortalite> registreDeces; // NOUVEAU : Liste des morts du tour


public :
   Milieu( int _width, int _height );
   ~Milieu( void );
   
   void initConfig(int nbEspeces);
   void initFromConfig(); // récupère les paramètres du fichier config
   
   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );
   std::vector<EspeceBestiole*> getListeEspeceBestioles() const {return listeEspeceBestioles;};
   
   void addMember( EspeceBestiole* b ) { listeEspeceBestioles.push_back(b); listeEspeceBestioles.back()->initCoords(width, height); }
   void addMember() {addMember(bestioleFactory->creerEspeceBestiole()); }
   
   int nbVoisins( const EspeceBestiole& b );
   void removeMember( EspeceBestiole* b );
   void removeDeds();
   void kill_all();
   void detecteCollisions();

   std::vector<StatMortalite> getAndClearRegistreDeces() {
        std::vector<StatMortalite> res = registreDeces;
        registreDeces.clear();
        return res;
    }

};

#endif