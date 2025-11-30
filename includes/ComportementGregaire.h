#ifndef _ComportementGregaire_
#define _ComportementGregaire_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <vector>

class ComportementGregaire : public Comportement
{

private :
    // Couleur RGB récupérée depuis le fichier de configuration
    static T couleur_cfg[3];
    
private:
    ComportementGregaire() {}
    ComportementGregaire(const ComportementGregaire&) = delete;
    ComportementGregaire& operator=(const ComportementGregaire&) = delete;
    
    // Couleur de la bestiole au comportement grégaire
    void initFromConfig();
    T * couleur;
    static ComportementGregaire* singletonGregaire;

public:
    static ComportementGregaire* getInstance();
    T * getCouleur() const override;
    std::string getNom() const override { return "Gregaire"; }
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const override;
};

#endif
