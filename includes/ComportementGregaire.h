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
    // Gestion du Singleton et de la Config (Architecture Main)
    static ComportementGregaire* singletonGregaire;
    static T couleur_cfg[3];
    static bool configInitialized;
    
private:
    ComportementGregaire() {}
    ComportementGregaire(const ComportementGregaire&) = delete;
    ComportementGregaire& operator=(const ComportementGregaire&) = delete;
    
    // Méthode interne pour charger la config
    void initFromConfig();

public:
    static ComportementGregaire* getInstance();

    // Méthodes requises par l'architecture Main
    Comportement* clone() const override;
    T * getCouleur() const override;
    
    // Attention : pas de const ici pour matcher la classe mère du Main
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    
    // Votre ajout pour l'analyse
    std::string getName() const override { return "Comportement Gregaire"; }
};

#endif