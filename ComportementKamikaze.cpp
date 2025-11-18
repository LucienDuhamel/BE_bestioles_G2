#include "Bestiole.h"
#include "ComportementKamikaze.h"
#include <iostream>
#include <vector>



ComportementKamikaze*   ComportementKamikaze::getInstance()
{
    if (singletonKamikaze == nullptr)
        singletonKamikaze = new ComportementKamikaze();

    return  singletonKamikaze;
}


void ComportementKamikaze::bouge(Bestiole bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    
}