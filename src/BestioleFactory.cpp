#include "BestioleFactory.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "utils.h"
#include <vector>
#include <cassert>

// Includes spécifiques aux accessoires (Version Main)
#include "Yeux.h"
#include "Oreilles.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Camouflage.h"
#include "config.h"
#include <cstdlib>

// Initialisation des membres statiques (Version Main)
double BestioleFactory::PROBA_YEUX = 0.5;
double BestioleFactory::PROBA_OREILLES = 0.5;
double BestioleFactory::PROBA_CARAPACE = 0.25;
double BestioleFactory::PROBA_NAGEOIRES = 0.5;
double BestioleFactory::PROBA_CAMOUFLAGE = 0.5;
bool BestioleFactory::configInitialized = false;

void BestioleFactory::initFromConfig() const {
    if (!configInitialized) {
        PROBA_YEUX = Config::getInstance().getDouble("PROBA_YEUX", 0.5);
        PROBA_OREILLES = Config::getInstance().getDouble("PROBA_OREILLES", 0.5);
        PROBA_CARAPACE = Config::getInstance().getDouble("PROBA_CARAPACE", 0.25);
        PROBA_NAGEOIRES = Config::getInstance().getDouble("PROBA_NAGEOIRES", 0.5);
        PROBA_CAMOUFLAGE = Config::getInstance().getDouble("PROBA_CAMOUFLAGE", 0.5);
        configInitialized = true;
    }
}

BestioleFactory::~BestioleFactory()
{
    // Nettoyage de la liste (nom variable version Main)
    listeComportements.clear();
    proportionsAccumilatives.clear();
}

BestioleFactory::BestioleFactory(std::vector<Comportement*> Comportements, std::vector<double> Proportions)
{
    assert(!Comportements.empty());
    // Assertion souple du main (accepte potentiellement une proportion finale implicite)
    assert(Comportements.size() == Proportions.size() || Comportements.size()+1 == Proportions.size());
    
    double accum=0.0;
    for (double x : Proportions ) accum+=x;
    assert( accum >= 0.99 && accum <= 1.01 ); // Petite tolérance aux flottants

    listeComportements.clear();
    for (auto& c : Comportements)
        listeComportements.push_back(std::move(c));

    proportionsAccumilatives.clear();
    proportionsAccumilatives.push_back(Proportions[0]);
    for (int i=1; i<(int)Proportions.size();i++ )
        proportionsAccumilatives.push_back(proportionsAccumilatives.back()+Proportions[i]);
}

Bestiole* BestioleFactory::creerEspeceBestiole() const
{
    // Chargement config au premier appel
    initFromConfig();
    
    Bestiole* bestiole = new Bestiole();
    double typeProb = randomBetween(0.0,1.0);
    int i=0;
    while( i<(int)proportionsAccumilatives.size()-1 && typeProb>=proportionsAccumilatives[i] ) i++ ;
    
    // CRUCIAL : Utilisation de clone() pour que chaque bestiole ait son propre état mental
    bestiole->setComportement(listeComportements[i]->clone());
        
    // Ajout aléatoire des capteurs (Logique Main)
    if (randomBetween(0.0, 1.0) < PROBA_YEUX) {
        bestiole->addCapteur(new Yeux());
    }

    if (randomBetween(0.0, 1.0) < PROBA_OREILLES) {
        bestiole->addCapteur(new Oreilles());
    }

    // Ajout aléatoire des accessoires (Logique Main)
    if (randomBetween(0.0, 1.0) < PROBA_CARAPACE) {
        bestiole->addAccessoire(new Carapace());
    }

    if (randomBetween(0.0, 1.0) < PROBA_NAGEOIRES) {
        bestiole->addAccessoire(new Nageoires());
    }

    if (randomBetween(0.0, 1.0) < PROBA_CAMOUFLAGE) {
        bestiole->addAccessoire(new Camouflage());
    }

    bestiole->setVitesseIni(bestiole->getVitesse());

    return bestiole;
}