main.o : main.cpp Aquarium.o Bestiole.o Milieu.o ComportementGregaire.o ComportementKamikaze.o ComportementPersoMultiples.o ComportementPeureux.o ComportementPrevoyant.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Milieu.o ComportementGregaire.o  ComportementKamikaze.o ComportementPersoMultiples.o ComportementPeureux.o ComportementPrevoyant.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

ComportementGregaire.o : ComportementGregaire.h ComportementGregaire.cpp
	g++ -Wall -std=c++11  -c ComportementGregaire.cpp -I .
ComportementKamikaze.o : ComportementKamikaze.h ComportementKamikaze.cpp
	g++ -Wall -std=c++11  -c ComportementKamikaze.cpp -I .
ComportementPersoMultiples.o : ComportementPersoMultiples.h ComportementPersoMultiples.cpp
	g++ -Wall -std=c++11  -c ComportementPersoMultiples.cpp -I .
ComportementPeureux.o : ComportementPeureux.h ComportementPeureux.cpp
	g++ -Wall -std=c++11  -c ComportementPeureux.cpp -I .
ComportementPrevoyant.o : ComportementPrevoyant.h ComportementPrevoyant.cpp
	g++ -Wall -std=c++11  -c ComportementPrevoyant.cpp -I .



clean:
	
	
	del /Q *.o
	del /Q *.exe


