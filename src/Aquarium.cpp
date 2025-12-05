#include "Aquarium.h"

#include "Milieu.h"

int Aquarium::NB_BESTIOLES_INIT = 0;

Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );
   initFromConfig();
   flotte->initConfig(NB_BESTIOLES_INIT);

}

// Initialisation des parametres statiques depuis le fichier de config (valeurs par defaut si absentes)
void Aquarium::initFromConfig() {
    NB_BESTIOLES_INIT = Config::getInstance().getInt("NB_BESTIOLES_INIT");
   }


Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}


void Aquarium::run(void)
{
    cout << "running Aquarium" << endl;
   bool Nopose = true;
    while (!is_closed())
    {
         wait(delay);
        if (is_key()) {
            int k = key();
            cout << "Vous avez presse la touche " << static_cast<unsigned char>(k);
            cout << " (" << k << ")" << endl;

            if ( is_keyESC() ) close();
            switch (k) {
                case 'q': // quit with 'q'
                    close();
                    break;
                case ' ': // spacebar
                    // toggle pause flag here
                    wait(3*delay);
                    Nopose = !Nopose;
                    break;
                case 'a':
                    cout << "Key A pressed: add a bestiole" << endl;
                    flotte->addMember();
                    break;
                case 'r':
                    cout << "Key R pressed: reset simulation" << endl;
                    // reset logic
                    flotte->initConfig(NB_BESTIOLES_INIT);
                    break;
                case 'k':
                    cout << "Key K pressed: kill everyone" << endl;
                    // reset logic
                    flotte->kill_all();
                    break;
                default:
                    cout << "Unhandled key" << endl;
                    break;
            }
        }


        if(Nopose){
            flotte->step();
         display(*flotte);
        }
        
        
    }
}

