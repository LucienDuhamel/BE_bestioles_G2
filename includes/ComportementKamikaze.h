#ifndef _ComportementKamikaze_
#define _ComportementKamikaze_

#include "Comportement.h"
#include "Bestiole.h"
#include "utils.h"

#include <iostream>
#include <vector>



class ComportementKamikaze : public Comportement
{

private:
    ComportementKamikaze() {}
    ComportementKamikaze(const ComportementKamikaze&) = delete;
    ComportementKamikaze& operator=(const ComportementKamikaze&) = delete;

    T* couleur;
    static ComportementKamikaze* singletonKamikaze;

public:
    static ComportementKamikaze* getInstance();

    T * getCouleur() const override;


    void reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&   listeBestioles ) const override;

    std::string getName() const override { return "Comportement Kamikaze"; }
    
};


#endif
