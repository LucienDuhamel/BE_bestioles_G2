#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"


#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<std::unique_ptr<Bestiole>>   listeBestioles;


public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   const auto& getListeBestioles() const { return listeBestioles; }

   void addMember(std::unique_ptr<Bestiole> b) {
    b->initCoords(width, height);
    listeBestioles.push_back(std::move(b));
   }

   int nbVoisins( const Bestiole & b );

};


#endif
