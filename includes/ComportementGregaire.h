#ifndef _ComportementGregaire_
#define _ComportementGregaire_

#include "Comportement.h"
#include "Bestiole.h"

#include <vector>
#include <string>

class ComportementGregaire : public Comportement
{
private:
    ComportementGregaire() {}
    ComportementGregaire(const ComportementGregaire&) = delete;
    ComportementGregaire& operator=(const ComportementGregaire&) = delete;

    T* couleur;

    static ComportementGregaire* singletonGregaire;

public:
    static ComportementGregaire* getInstance();

    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const override;

    T * getCouleur() const override;


    std::string getName() const override { return "Comportement Gregaire"; }
};

#endif
