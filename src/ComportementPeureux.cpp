#include "Bestiole.h"
#include "ComportementPeureux.h"
#include "utils.h"

#include <iostream>
#include <vector>


ComportementPeureux* ComportementPeureux::singletonPeureux = nullptr;



ComportementPeureux*   ComportementPeureux::getInstance()
{
    if (singletonPeureux == nullptr){
        singletonPeureux = new ComportementPeureux();
        singletonPeureux->couleur = new T[ 3 ];

        // Couleur vert clair
        singletonPeureux->couleur[ 0 ] = 34;
        singletonPeureux->couleur[ 1 ] = 177;
        singletonPeureux->couleur[ 2 ] = 76;

    }

    return  singletonPeureux;
}

T * ComportementPeureux::getCouleur()  const  {
    return couleur;
}


void ComportementPeureux::reagit(
    Bestiole& bestiole,
    const std::vector<EspeceBestiole*>& listeBestioles
) const
{
    // Liste des bestioles visibles
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    // Si assez d'individus pour être effrayé
    if (bestiolesVisibles.size() > BESTIOLE_SCARED_NUMBER)
    {
        // Calcul du barycentre des positions
        int bx = 0.0, by = 0.0;
        for (EspeceBestiole* b : bestiolesVisibles)
        {
            bx += b->getX();
            by += b->getY();
        }

        bx /= bestiolesVisibles.size();
        by /= bestiolesVisibles.size();

        // Fuite : orientation opposée au barycentre
        bestiole.setOrientation(
            calcOrientation(bestiole.getX(), bestiole.getY(), bx, by) + M_PI
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