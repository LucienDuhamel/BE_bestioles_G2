#ifndef _ComportementPersoMultiples_
#define _ComportementPersoMultiples_


#include "Bestiole.h"
#include "Comportement.h"

#include <iostream>
#include <vector>



class ComportementPersoMultiples : public Comportement
{
private:
   std::vector<Comportement*> ListComportements;


    ComportementPersoMultiples() {}
    ComportementPersoMultiples(std::vector<Comportement*> ListComportement);
    ComportementPersoMultiples(const ComportementPersoMultiples&) = delete;
    ComportementPersoMultiples& operator=(const ComportementPersoMultiples&) = delete;

    static ComportementPersoMultiples* singletonPersoMultiples;

public:

    ~ComportementPersoMultiples();
    static ComportementPersoMultiples* getInstance(std::vector<Comportement*> ListComportement) ;
    static ComportementPersoMultiples* getInstance() ;


    void bouge(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const override;

};


#endif
