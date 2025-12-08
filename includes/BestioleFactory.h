#ifndef _BestioleFactory_H_
#define _BestioleFactory_H_

#include "EspeceBestioleFactory.h"
#include "Bestiole.h" // <--- AJOUT OBLIGATOIRE pour le type covariant
#include "Comportement.h"
#include <vector>

class BestioleFactory : public EspeceBestioleFactory
{
private:
    std::vector<Comportement*> listeComportements;
    std::vector<double> proportionsAccumilatives;

    // Paramètres de configuration (correspondance avec le .cpp)
    static double PROBA_YEUX;
    static double PROBA_OREILLES;
    static double PROBA_CARAPACE;
    static double PROBA_NAGEOIRES;
    static double PROBA_CAMOUFLAGE;
    static bool configInitialized;
    
    void initFromConfig() const;

public:
    BestioleFactory(std::vector<Comportement*> Comportements, std::vector<double> Proportions);
    virtual ~BestioleFactory();
    
    // Le compilateur acceptera Bestiole* car il connait l'héritage grâce à l'include
    Bestiole* creerEspeceBestiole() const override;
};

#endif