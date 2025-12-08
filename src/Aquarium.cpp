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
// Fonction utilitaire pour le graphique (Version CImg Native avec Echelles)
void plotPopulation(const std::vector<Stat>& stats) {
    if (stats.empty()) return;

    // Dimensions du graphique
    const int w = 800;
    const int h = 600;
    // On augmente la marge gauche pour laisser la place aux chiffres de l'axe Y
    const int margin_left = 50; 
    const int margin_bottom = 40;
    const int margin_top = 20;
    const int margin_right = 20;

    // Création de l'image (Fond blanc)
    cimg_library::CImg<unsigned char> graph(w, h, 1, 3, 255);
    
    // Couleurs
    const unsigned char bleu[] = {0, 0, 255};
    const unsigned char rouge[] = {255, 0, 0};
    const unsigned char vert[] = {0, 200, 0};
    const unsigned char orange[] = {255, 165, 0};
    const unsigned char violet[] = {128, 0, 128};
    const unsigned char noir[] = {0, 0, 0};
    const unsigned char gris[] = {220, 220, 220};

    // Trouver les maximums pour l'échelle
    int maxTime = stats.back().time;
    if (maxTime == 0) maxTime = 1;

    int maxPop = 0;
    for (const auto& s : stats) {
        int total = s.nbGreguaires + s.nbPeureuses + s.nbKamikazes + s.nbPersoMultiples + s.nbPrevoyants;
        if (total > maxPop) maxPop = total;
    }
    // Marge de sécurité pour le haut du graphe
    maxPop = (int)(maxPop * 1.1); 
    if (maxPop == 0) maxPop = 1;

    // Fonctions lambda pour convertir les coordonnées
    // Zone de tracé : de margin_left à w-margin_right
    //                 de h-margin_bottom à margin_top
    auto getX = [&](int time) { 
        return margin_left + (time * (w - margin_left - margin_right)) / maxTime; 
    };
    auto getY = [&](int nb) { 
        return h - margin_bottom - (nb * (h - margin_bottom - margin_top)) / maxPop; 
    };

    // --- Dessin de la grille et des axes ---
    
    // Cadre de la zone de tracé
    graph.draw_rectangle(margin_left, margin_top, w-margin_right, h-margin_bottom, gris, 0.1f);
    
    // Axes
    graph.draw_line(margin_left, h-margin_bottom, w-margin_right, h-margin_bottom, noir); // Axe X
    graph.draw_line(margin_left, margin_top, margin_left, h-margin_bottom, noir);         // Axe Y

    // --- Ajout des échelles (Texte) ---
    
    // Echelle Y (Population) : 0, max/2, max
    graph.draw_text(5, h - margin_bottom - 5, "0", noir, 0, 1, 13);
    graph.draw_text(5, getY(maxPop/2) - 5, std::to_string(maxPop/2).c_str(), noir, 0, 1, 13);
    graph.draw_text(5, margin_top, std::to_string(maxPop).c_str(), noir, 0, 1, 13);
    
    // Echelle X (Temps) : 0, max/2, max
    graph.draw_text(margin_left, h - margin_bottom + 5, "0", noir, 0, 1, 13);
    graph.draw_text(getX(maxTime/2), h - margin_bottom + 5, std::to_string(maxTime/2).c_str(), noir, 0, 1, 13);
    graph.draw_text(w - margin_right - 20, h - margin_bottom + 5, std::to_string(maxTime).c_str(), noir, 0, 1, 13);
    
    // Titres des axes
    graph.draw_text(w/2, h - 20, "Temps (steps)", noir, 0, 1, 16);
    graph.draw_text(10, h/2, "Pop.", noir, 0, 1, 16, 90); // 90 degrés si supporté, sinon horizontal

    // ----------------------------------

    // Tracer les courbes
    for (size_t i = 1; i < stats.size(); ++i) {
        int x0 = getX(stats[i-1].time);
        int x1 = getX(stats[i].time);

        // Gregaires (Bleu)
        graph.draw_line(x0, getY(stats[i-1].nbGreguaires), x1, getY(stats[i].nbGreguaires), bleu);
        // Peureuses (Rouge)
        graph.draw_line(x0, getY(stats[i-1].nbPeureuses), x1, getY(stats[i].nbPeureuses), rouge);
        // Kamikazes (Vert)
        graph.draw_line(x0, getY(stats[i-1].nbKamikazes), x1, getY(stats[i].nbKamikazes), vert);
        // PersoMultiples (Orange)
        graph.draw_line(x0, getY(stats[i-1].nbPersoMultiples), x1, getY(stats[i].nbPersoMultiples), orange);
        // Prevoyants (Violet)
        graph.draw_line(x0, getY(stats[i-1].nbPrevoyants), x1, getY(stats[i].nbPrevoyants), violet);
    }

    // Légende (déplacée légèrement pour ne pas chevaucher l'axe Y)
    int lx = margin_left + 20; 
    int ly = margin_top + 10;
    graph.draw_text(lx, ly, "Gregaires", bleu, 0, 1, 13); ly += 15;
    graph.draw_text(lx, ly, "Peureuses", rouge, 0, 1, 13); ly += 15;
    graph.draw_text(lx, ly, "Kamikazes", vert, 0, 1, 13); ly += 15;
    graph.draw_text(lx, ly, "PersoMultiples", orange, 0, 1, 13); ly += 15;
    graph.draw_text(lx, ly, "Prevoyants", violet, 0, 1, 13);

    // Affichage dans une fenêtre
    cimg_library::CImgDisplay disp(graph, "Evolution de la population (Fermez pour quitter)");
    while (!disp.is_closed()) {
        disp.wait();
    }
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