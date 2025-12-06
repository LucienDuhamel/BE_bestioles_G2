#ifndef _BestioleFactory_
#define _BestioleFactory_

#include "config.h"
#include "EspeceBestiole.h"
#include "Comportement.h"
#include "EspeceBestioleFactory.h"
#include <vector>

class BestioleFactory : public EspeceBestioleFactory
{
private:
    std::vector<Comportement*> listeComportements;
    std::vector<double> proportionsAccumilatives;
    
    // Probabilités statiques récupérées depuis le fichier de configuration
    static double PROBA_YEUX;
    static double PROBA_OREILLES;
    static double PROBA_CARAPACE;
    static double PROBA_NAGEOIRES;
    static double PROBA_CAMOUFLAGE;
    static bool configInitialized;
    
    void initFromConfig() const;
public :
    ~BestioleFactory();
    BestioleFactory(std::vector<Comportement*> Comportements, std::vector<double> Proportions);
    Bestiole* creerEspeceBestiole() const override;

};


#endif
