#include "Bestiole.h"
#include "ComportementPeureux.h"


void ComportementPeureux::bouge(Bestiole& b) const
{   

    bool simJustStarted = false;
    bool isScared = false;
    const auto& liste = b.getListeBestiolesDetectees();
    int nbStep = 0; // Nombre d'étapes restantes à être effrayé.
    double vIni = 0.0;

    if (simJustStarted){
        vIni = b.getVitesse();
        simJustStarted = false;
    } // end if

    if (liste.size()>BESTIOLE_SCARED_NUMBER){
        double mX = 0.0; double mY = 0.0;
        for (Bestiole* other : liste){
            mX += other->getX();;
            mY += other->getY();
        } // end for

        mX /= liste.size();
        mY /= liste.size();
 
        // On fuit le barycentre des positions des bestioles détectées.
        b.setOrientation(calcOrientation(b.getX(), b.getY(), mX, mY) + M_PI);

        if (!isScared){
            isScared = true;
            b.setVitesse(vIni * SPEED_COEF);

        } //end if

        nbStep = REMAINING_SCARED_STEPS; // Nombre d'étapes restantes à être effrayé.

    } //end if

    else {
        if (nbStep > 0) {
            if (isScared){
                isScared = false;
            } //end if 

        nbStep -= 1;

        } // end if

        else {
            // On revient à la vitesse normale.
            b.setVitesse(vIni);
        }// end else

    }// end else

}


string ComportementPeureux::getNameComportement() const
{
    return "peureux";
}
