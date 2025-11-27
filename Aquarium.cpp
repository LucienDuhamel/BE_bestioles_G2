#include "Aquarium.h"

#include "Milieu.h"
#include "Simulation.h"


Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" );

   simulation = new Simulation( *flotte );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}


Aquarium::~Aquarium( void )
{

   delete flotte;

   delete simulation;

   cout << "dest Aquarium" << endl;

}

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


void Aquarium::run( void )
{

   cout << "running Aquarium" << endl;

   while ( ! is_closed() )
   {

      // cout << "iteration de la simulation" << endl;

      if ( is_key() ) {
         cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if ( is_keyESC() ) close();
      }

      flotte->step();
      display( *flotte );

      simulation->step();

      wait( delay );

   } // while

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

   // Après la boucle de simulation
   plotPopulation(simulation->getStatistics());


}
