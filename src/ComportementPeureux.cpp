#include "Bestiole.h"
#include "ComportementPeureux.h"
#include "utils.h"

#include <iostream>
#include <vector>

T ComportementPeureux::couleur_cfg[3] = {0, 0, 0};

ComportementPeureux* ComportementPeureux::singletonPeureux = nullptr;
int ComportementPeureux::BESTIOLE_SCARED_NUMBER = 0;
int ComportementPeureux::REMAINING_SCARED_STEPS = 0;
double ComportementPeureux::SPEED_COEF = 0.0;

ComportementPeureux*   ComportementPeureux::getInstance()
{
    if (singletonPeureux == nullptr){
        singletonPeureux = new ComportementPeureux();
        singletonPeureux->couleur = new T[ 3 ];

        if((couleur_cfg[0]==0 && couleur_cfg[1]==0 && couleur_cfg[2]==0)
            || BESTIOLE_SCARED_NUMBER==0 
            || REMAINING_SCARED_STEPS==0
            || SPEED_COEF == 0.0) {
            singletonPeureux->initFromConfig();
        }

        // Couleur vert clair
        singletonPeureux->couleur[ 0 ] = couleur_cfg[0];
        singletonPeureux->couleur[ 1 ] = couleur_cfg[1];
        singletonPeureux->couleur[ 2 ] = couleur_cfg[2];

    }

    return  singletonPeureux;
}

void ComportementPeureux::initFromConfig() {
    // par défaut : vert clair
    couleur_cfg[0] = Config::getInstance().getInt("PEU_COULEUR_R", 34);
    couleur_cfg[1] = Config::getInstance().getDouble("PEU_COULEUR_G", 177);
    couleur_cfg[2] = Config::getInstance().getDouble("PEU_COULEUR_B", 76);

    BESTIOLE_SCARED_NUMBER = Config::getInstance().getInt("BESTIOLE_SCARED_NUMBER", 3);
    REMAINING_SCARED_STEPS = Config::getInstance().getInt("REMAINING_SCARED_STEPS", 2);
    SPEED_COEF = Config::getInstance().getDouble("SPEED_COEF", 5);
}

T * ComportementPeureux::getCouleur()  const  {
    return couleur;
}


void ComportementPeureux::reagit(
    Bestiole& bestiole,
    const std::vector<EspeceBestiole*>& listeBestioles
) const
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    // Si assez d'individus pour être effrayé
    if (static_cast<int>(bestiolesVisibles.size()) >= BESTIOLE_SCARED_NUMBER)
    {
        // Calcul du barycentre des positions
        double bx = 0.0, by = 0.0;
        for (EspeceBestiole* b : bestiolesVisibles) {
            bx += static_cast<double>(b->getX());
            by += static_cast<double>(b->getY());
        }
        bx /= static_cast<double>(bestiolesVisibles.size());
        by /= static_cast<double>(bestiolesVisibles.size());

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
        // Encore effrayée ?
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

    std::cout << "Bestiole (" << bestiole.getId() << ") : "
              << (isScared ? "Effrayée" : "Calme") 
              << ", Vitesse = " << bestiole.getVitesse() 
              << ", Étapes restantes effrayée = " << nbStep 
              << "Vitesse initiale = " << vIni
              << std::endl;


}

