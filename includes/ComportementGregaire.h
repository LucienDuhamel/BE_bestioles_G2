#ifndef _ComportementGregaire_
#define _ComportementGregaire_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <vector>

class ComportementGregaire : public Comportement
{

private :
    static ComportementGregaire* singletonGregaire;
    static T couleur_cfg[3];
    static bool configInitialized;
    
private:
    ComportementGregaire() {}
    ComportementGregaire(const ComportementGregaire&) = delete;
    ComportementGregaire& operator=(const ComportementGregaire&) = delete;
    void initFromConfig();

public:
    static ComportementGregaire* getInstance();
    Comportement* clone() const override;
    T * getCouleur() const override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    
};

#endif
