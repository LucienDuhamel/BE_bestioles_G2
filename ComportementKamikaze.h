#ifndef _ComportementKamikaze_
#define _ComportementKamikaze_

#include "Comportement.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>



class ComportementKamikaze : public Comportement
{

private:
    ComportementKamikaze() {}
    ComportementKamikaze(const ComportementKamikaze&) = delete;
    ComportementKamikaze& operator=(const ComportementKamikaze&) = delete;

    static ComportementKamikaze* singletonKamikaze;

public:
    static ComportementKamikaze* getInstance();


    void bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const override;

    std::string getName() const override { return "Comportement Kamikaze"; }

};


#endif
