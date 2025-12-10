#ifndef _ComportementGregaire_
#define _ComportementGregaire_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <vector>
#include <string>

class ComportementGregaire : public Comportement
{

private :
    // Gestion du Singleton et de la Config
    static ComportementGregaire* singletonGregaire;
    static T COULEUR_CFG[3];
    static bool configInitialized;
    
private:
    ComportementGregaire() {}
    ComportementGregaire(const ComportementGregaire&) = delete;
    ComportementGregaire& operator=(const ComportementGregaire&) = delete;
    
private:
    void initFromConfig();

public:
    static ComportementGregaire* getInstance();
    Comportement* clone() const override;

    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    
    T * getCouleur() const override;
    std::string getName() const override { return "Comportement Gregaire"; }
};

#endif