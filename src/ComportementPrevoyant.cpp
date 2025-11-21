#include "Bestiole.h"
#include "ComportementPrevoyant.h"

void ComportementPrevoyant::bouge(Bestiole& b) const
{   
    
    // double v_other_bestiole
    // for ( std::vector<Bestiole>::iterator it = listeBestiolesDetectees.begin() ; it != listeBestiolesDetectees.end() ; ++it ){
    //         mX += (*it).getX();
    //         mY += (*it).getY();
    //     } // end for
}

string ComportementPrevoyant::getNameComportement() const
{
    return "prevoyant";
}