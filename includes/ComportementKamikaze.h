#ifndef _ComportementKamikaze_
#define _ComportementKamikaze_

#include "config.h"
#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementKamikaze : public Comportement
{

private: 
    static T couleur_cfg[3];

private:
    ComportementKamikaze() {}
    ComportementKamikaze(const ComportementKamikaze&) = delete;
    ComportementKamikaze& operator=(const ComportementKamikaze&) = delete;

    void initFromConfig();
    static ComportementKamikaze* singletonKamikaze;

public:
    static ComportementKamikaze* getInstance();
    Comportement* clone() const override;
    T * getCouleur()  const  override;
    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) override;
    
};


#endif
