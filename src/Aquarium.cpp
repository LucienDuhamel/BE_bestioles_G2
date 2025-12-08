#include "Aquarium.h"
#include "Milieu.h"
#include "Simulation.h" 

// Initialisation des membres statiques (Version Main)
int Aquarium::NB_BESTIOLES_INIT = 0;
bool Aquarium::configInitialized = false;

Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{
   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();

   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" );

   // Initialisation de VOTRE simulation (Version HEAD)
   simulation = new Simulation( *flotte );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

   // Chargement de la config (Version Main)
   if (!configInitialized) {
       initFromConfig();
       configInitialized = true;
   }
   flotte->initConfig(NB_BESTIOLES_INIT);
}

// Initialisation des parametres statiques depuis le fichier de config
void Aquarium::initFromConfig() {
    NB_BESTIOLES_INIT = Config::getInstance().getInt("NB_BESTIOLES_INIT", 20);
}

Aquarium::~Aquarium( void )
{
   delete flotte;
   delete simulation; // Ne pas oublier de supprimer votre simulation !
   cout << "dest Aquarium" << endl;
}

// Fonction utilitaire pour le graphique (Version HEAD)
void plotPopulation(const std::vector<Stat>& stats) {
    if (stats.empty()) return;

    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        std::cerr << "Erreur : impossible d'ouvrir gnuplot\n";
        return;
    }

    fprintf(gp, "set title 'Evolution de la population par comportement'\n");
    fprintf(gp, "set xlabel 'Temps'\n");
    fprintf(gp, "set ylabel 'Nombre de bestioles'\n");
    fprintf(gp, "set grid\n");

    // Préparer les données
    fprintf(gp, "$data << EOD\n");
    for (const auto& s : stats) {
        fprintf(gp, "%d %d %d %d %d %d\n", s.time, s.nbGreguaires, s.nbPeureuses, s.nbKamikazes, s.nbPersoMultiples, s.nbPrevoyants);
    }
    fprintf(gp, "EOD\n");

    // Tracer toutes les colonnes correctement
    fprintf(gp,
        "plot $data using 1:2 with lines title 'Gregaires' lw 2 lc rgb 'blue', "
        "$data using 1:3 with lines title 'Peureuses' lw 2 lc rgb 'red', "
        "$data using 1:4 with lines title 'Kamikazes' lw 2 lc rgb 'green', "
        "$data using 1:5 with lines title 'PersoMultiples' lw 2 lc rgb 'orange', "
        "$data using 1:6 with lines title 'Prevoyants' lw 2 lc rgb 'purple'\n"
    );

    fflush(gp);
}

void Aquarium::run(void)
{
    cout << "running Aquarium" << endl;
    bool Nopose = true;

    while (!is_closed())
    {
        wait(delay);
        
        // Gestion des entrées clavier (Version Main - Très complet)
        if (is_key()) {
            int k = key();
            cout << "Vous avez presse la touche " << static_cast<unsigned char>(k);
            cout << " (" << k << ")" << endl;

            if ( is_keyESC() ) close();
            switch (k) {
                case 'q': // quit with 'q'
                    close();
                    break;
                case ' ': // spacebar : Pause
                    wait(3*delay); // petite pause pour éviter le rebond
                    Nopose = !Nopose;
                    break;
                case 'a': // Add
                    cout << "Key A pressed: add a bestiole" << endl;
                    flotte->addMember();
                    break;
                case 'r': // Reset
                    cout << "Key R pressed: reset simulation" << endl;
                    flotte->initConfig(NB_BESTIOLES_INIT);
                    break;
                case 'k': // Kill all
                    cout << "Key K pressed: kill everyone" << endl;
                    flotte->kill_all();
                    break;
                default:
                    // cout << "Unhandled key" << endl;
                    break;
            }
        }

        // Boucle de simulation si pas en pause
        if(Nopose){
            flotte->step();
            simulation->step(); // J'ai inséré VOTRE étape d'enregistrement ici
            display(*flotte);
        }
    }

    // Affichage des statistiques à la fin (Version HEAD)
    std::cout << "\n=== Population finale par type ===\n";
    const auto& stats = simulation->getStatistics();

    if (!stats.empty()) 
    {
        const Stat& last = stats.back();
        std::cout << "Temps " << last.time << " : \n";
        std::cout << "  Gregaires : " << last.nbGreguaires << "\n";
        std::cout << "  Peureuses : " << last.nbPeureuses << "\n";
        std::cout << "  Kamikazes : " << last.nbKamikazes << "\n";
        std::cout << "  PersoMultiples : " << last.nbPersoMultiples << "\n";
        std::cout << "  Prevoyants : " << last.nbPrevoyants << "\n";
        std::cout << "  Total     : " << (last.nbGreguaires + last.nbPeureuses + last.nbKamikazes + last.nbPersoMultiples + last.nbPrevoyants) << "\n";
    }
    simulation -> afficherBilanFinal(); // <--- AJOUTER CECI
    plotPopulation(simulation->getStatistics());
}