#include "Bestiole.h"
#include "ComportementPeureux.h"
#include <iostream>
#include <vector>


ComportementPeureux* ComportementPeureux::singletonPeureux = nullptr;



ComportementPeureux*   ComportementPeureux::getInstance()
{
    if (singletonPeureux == nullptr)
        singletonPeureux = new ComportementPeureux();

    return  singletonPeureux;
}


void ComportementPeureux::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    // Liste des bestioles visibles
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    // Si assez d'individus pour être effrayé
    if (bestiolesVisibles.size() > BESTIOLE_SCARED_NUMBER)
    {
        // Calcul du barycentre des positions
        double bx = 0.0, by = 0.0;
        for (Bestiole* b : bestiolesVisibles)
        {
            bx += b->getx();
            by += b->gety();
        }

        bx /= bestiolesVisibles.size();
        by /= bestiolesVisibles.size();

        // Fuite : orientation opposée au barycentre
        bestiole.setOrientation(
            calcOrientation(bestiole.getx(), bestiole.gety(), bx, by) + M_PI
        );

        // Activation du mode "effrayé"
        if (!isScared)
        {
            isScared = true;
            vIni = bestiole.getVitesse();   // Sauvegarde de la vitesse d'origine
            bestiole.setVitesse(vIni * SPEED_COEF);
        }

        nbStep = REMAINING_SCARED_STEPS;
    }
    else
    {
        // Encore effrayé ?
        if (nbStep > 0)
        {
            nbStep--;

            if (nbStep == 0)
            {
                // Retour vitesse normale
                bestiole.setVitesse(vIni);
                isScared = false;
            }
        }
    }
    
}