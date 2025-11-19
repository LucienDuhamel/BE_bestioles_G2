#ifndef _ComportementGregaire_
#define _ComportementGregaire_

#include "Comportement.h"
#include "Bestiole.h"

#include <vector>

class ComportementGregaire : public Comportement
{
private:
    ComportementGregaire() {}
    ComportementGregaire(const ComportementGregaire&) = delete;
    ComportementGregaire& operator=(const ComportementGregaire&) = delete;

    static ComportementGregaire* singletonGregaire;

public:
    static ComportementGregaire* getInstance();

    void bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const override;
};

#endif
