#include "Aquarium.h"
#include "Milieu.h"
#include "Simulation.h" 

// Initialisation des membres statiques (Version Main)
int Aquarium::NB_BESTIOLES_INIT = 0;
bool Aquarium::configInitialized = false;

// Dimensions de l'écran (pour centrer la fenêtre)
bool Aquarium::ACTIVATED_ANALYSE = false;
int Aquarium::GRAPHIC_WIDTH = -1;
int Aquarium::GRAPHIC_HEIGHT = -1;

Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();

   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" );

   // Chargement de la config (Version Main)
   if (!configInitialized) {
       initFromConfig();
       configInitialized = true;
   }
   
   // Initialisation de VOTRE simulation (Version HEAD)
   if (ACTIVATED_ANALYSE) {
       simulation = new Simulation( *flotte );
   }

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

   flotte->initConfig(NB_BESTIOLES_INIT);
}

// Initialisation des parametres statiques depuis le fichier de config
void Aquarium::initFromConfig() {
    NB_BESTIOLES_INIT = Config::getInstance().getInt("NB_BESTIOLES_INIT", 20);
    ACTIVATED_ANALYSE = Config::getInstance().getBool("ACTIVATED_ANALYSE", false);
    GRAPHIC_WIDTH = Config::getInstance().getInt("GRAPHIC_WIDTH", 900);
    GRAPHIC_HEIGHT = Config::getInstance().getInt("GRAPHIC_HEIGHT", 600);
}

Aquarium::~Aquarium( void )
{
   delete flotte;
   delete simulation; // Ne pas oublier de supprimer votre simulation !
   cout << "dest Aquarium" << endl;
}
// Fonction utilitaire pour le graphique (Version Améliorée avec Grille et Graduations)
void plotPopulation(const std::vector<Stat>& stats) {
    if (stats.empty()) return;

    // Dimensions du graphique
    const int GRAPHIC_WIDTH = 900;  // Un peu plus large
    const int GRAPHIC_HEIGHT = 600;
    
    // Marges (Gauche plus large pour les nombres > 100)
    const int margin_left = 60; 
    const int margin_bottom = 50;
    const int margin_top = 30;
    const int margin_right = 30;

    // Création de l'image (Fond blanc)
    cimg_library::CImg<unsigned char> graph(GRAPHIC_WIDTH, GRAPHIC_HEIGHT, 1, 3, 255);
    
    // Couleurs
    const unsigned char bleu[] = {0, 0, 255};
    const unsigned char rouge[] = {255, 0, 0};
    const unsigned char vert[] = {0, 200, 0};
    const unsigned char orange[] = {255, 165, 0};
    const unsigned char violet[] = {128, 0, 128};
    const unsigned char noir[] = {0, 0, 0};
    const unsigned char gris_clair[] = {220, 220, 220}; // Pour la grille

    // 1. Calcul des Maximums
    int maxTime = stats.back().time;
    if (maxTime == 0) maxTime = 1;

    int maxPop = 0;
    for (const auto& s : stats) {
        int total = s.nbGreguaires + s.nbPeureuses + s.nbKamikazes + s.nbPersoMultiples + s.nbPrevoyants;
        if (total > maxPop) maxPop = total;
    }
    // Marge de sécurité de 10% en haut
    maxPop = (int)(maxPop * 1.1); 
    if (maxPop == 0) maxPop = 10;

    // 2. Fonctions de conversion (Valeur -> Pixel)
    auto getX = [&](int time) { 
        return margin_left + (int)((long long)time * (GRAPHIC_WIDTH - margin_left - margin_right) / maxTime); 
    };
    auto getY = [&](int nb) { 
        return GRAPHIC_HEIGHT - margin_bottom - (int)((long long)nb * (GRAPHIC_HEIGHT - margin_bottom - margin_top) / maxPop); 
    };

    // 3. Dessin de la Grille et des Axes (Amélioré)
    
    // --- Axe Y (Population) ---
    // On veut environ 10 graduations
    int stepY = maxPop / 10; 
    if (stepY < 1) stepY = 1;
    
    // Arrondir le step à une valeur "propre" (5, 10, 50, etc.) si possible, 
    // mais ici un step linéaire simple suffit pour commencer.
    for (int v = 0; v <= maxPop; v += stepY) {
        int y = getY(v);
        // Ligne de grille horizontale
        graph.draw_line(margin_left, y, GRAPHIC_WIDTH - margin_right, y, gris_clair);
        // Tiret sur l'axe
        graph.draw_line(margin_left - 5, y, margin_left, y, noir);
        // Texte de valeur
        graph.draw_text(5, y - 5, std::to_string(v).c_str(), noir, 0, 1, 13);
    }

    // --- Axe X (Temps) ---
    int stepX = maxTime / 10;
    if (stepX < 1) stepX = 1;

    for (int t = 0; t <= maxTime; t += stepX) {
        int x = getX(t);
        // Ligne de grille verticale
        graph.draw_line(x, margin_top, x, GRAPHIC_HEIGHT - margin_bottom, gris_clair);
        // Tiret sur l'axe
        graph.draw_line(x, GRAPHIC_HEIGHT - margin_bottom, x, GRAPHIC_HEIGHT - margin_bottom + 5, noir);
        // Texte de valeur
        graph.draw_text(x - 10, GRAPHIC_HEIGHT - margin_bottom + 10, std::to_string(t).c_str(), noir, 0, 1, 13);
    }

    // Dessiner les axes principaux par-dessus la grille
    graph.draw_line(margin_left, GRAPHIC_HEIGHT - margin_bottom, GRAPHIC_WIDTH - margin_right, GRAPHIC_HEIGHT - margin_bottom, noir); // Axe X
    graph.draw_line(margin_left, margin_top, margin_left, GRAPHIC_HEIGHT - margin_bottom, noir);             // Axe Y

    // Titres des axes
    graph.draw_text(GRAPHIC_WIDTH / 2, GRAPHIC_HEIGHT - 20, "Temps (steps)", noir, 0, 1, 16);
    // Pour l'axe Y vertical, CImg ne gère pas toujours bien la rotation de texte simple, 
    // on le met donc au sommet de l'axe Y.
    graph.draw_text(margin_left + 10, margin_top - 10, "Population", noir, 0, 1, 16);


    // 4. Tracer les courbes
    for (size_t i = 1; i < stats.size(); ++i) {
        int x0 = getX(stats[i-1].time);
        int x1 = getX(stats[i].time);

        // On dessine avec une épaisseur de trait simulée (en décalant de 1px) pour plus de visibilité
        auto draw_thick = [&](int y0, int y1, const unsigned char* col) {
            graph.draw_line(x0, y0, x1, y1, col);
            graph.draw_line(x0, y0+1, x1, y1+1, col); // Effet gras
        };

        draw_thick(getY(stats[i-1].nbGreguaires), getY(stats[i].nbGreguaires), bleu);
        draw_thick(getY(stats[i-1].nbPeureuses), getY(stats[i].nbPeureuses), rouge);
        draw_thick(getY(stats[i-1].nbKamikazes), getY(stats[i].nbKamikazes), vert);
        draw_thick(getY(stats[i-1].nbPersoMultiples), getY(stats[i].nbPersoMultiples), orange);
        draw_thick(getY(stats[i-1].nbPrevoyants), getY(stats[i].nbPrevoyants), violet);
    }

    // 5. Légende (Box semi-transparente simulée par un rectangle blanc encadré)
    int lx = GRAPHIC_WIDTH - 160; 
    int ly = margin_top + 10;
    
    // Fond de légende
    graph.draw_rectangle(lx - 10, ly - 10, lx + 130, ly + 95, gris_clair, 0.8f);
    graph.draw_rectangle(lx - 10, ly - 10, lx + 130, ly + 95, noir, 1, ~0U); // Contour

    auto draw_legend_item = [&](const char* label, const unsigned char* col, int& y) {
        graph.draw_rectangle(lx, y, lx+15, y+10, col);
        graph.draw_text(lx + 25, y-2, label, noir, 0, 1, 13);
        y += 18;
    };

    draw_legend_item("Gregaires", bleu, ly);
    draw_legend_item("Peureuses", rouge, ly);
    draw_legend_item("Kamikazes", vert, ly);
    draw_legend_item("PersoMultiples", orange, ly);
    draw_legend_item("Prevoyants", violet, ly);

    // Affichage
    cimg_library::CImgDisplay disp(graph, "Statistiques de Population");
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
            if (ACTIVATED_ANALYSE)
                simulation->step(); // J'ai inséré VOTRE étape d'enregistrement ici
            display(*flotte);
        }
    }

    // Affichage des statistiques à la fin (Version HEAD)
    if (ACTIVATED_ANALYSE){
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
        simulation -> afficherBilanFinal();
        plotPopulation(simulation->getStatistics());
    }
}