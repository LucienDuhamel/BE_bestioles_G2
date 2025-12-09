#ifndef UTILS
#define UTILS

#include "Bestiole.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <random>

using namespace std;

// Déclaration des fonctions utilitaires
double randomBetween(double a, double b);

std::unordered_map<std::string, std::string> loadJSONConfig(const std::string& filename);

template <typename T>
double calcDistance(T x1, T y1, T x2, T y2)
{
    double dx = static_cast<double>(x1) - static_cast<double>(x2);
    double dy = static_cast<double>(y1) - static_cast<double>(y2);
    return std::sqrt(dx*dx + dy*dy);
}

template <typename B, typename C>
double calcDistance(const B& b, const C& c)
{
    return calcDistance(b.getX(), b.getY(), c.getX(), c.getY());
}

template<typename T, typename U>
double calcOrientation(T x1 , T y1, U x2, U y2) {
    double dx = static_cast<double>(x2) - static_cast<double>(x1);  // cible - bestiole
    double dy = static_cast<double>(y2) - static_cast<double>(y1);

    // atan2 gère tous les quadrants et la division par zéro
    return std::atan2(-dy, dx); 
}

template <typename B, typename C>
double calcOrientation(const B& b, const C& c)
{
    return calcOrientation(b.getX(), b.getY(), c.getX(), c.getY());
}

template <typename T>
double calcMoyenne(std::vector<T> const& values)
{
    if (values.empty()) {
        return 0.0; 
    }

    double sum = 0.0;
    for (const auto& value : values) {
        sum += static_cast<double>(value);
    }
    return sum / static_cast<double>(values.size());
}

template<typename X1, typename Y1, typename S1,
         typename X2, typename Y2, typename S2>
bool isInHitBox(X1 x1, Y1 y1, S1 size1,
                X2 x2, Y2 y2, S2 size2)
{
    double dx = static_cast<double>(x1) - static_cast<double>(x2);
    double dy = static_cast<double>(y1) - static_cast<double>(y2);
    double dist2 = dx*dx + dy*dy;

    // Rayon = moitié de la taille affichée
    // On suppose que toutes les bestioles ont une hitbox circulaire
    double r1 = static_cast<double>(size1) * 0.5;
    double r2 = static_cast<double>(size2) * 0.5;

    double minDist = r1 + r2;

    return dist2 < (minDist * minDist);
}

template<typename B1, typename B2>
bool isInHitBox(const B1& b1, const B2& b2)
{
    return isInHitBox(
        b1.getX(), b1.getY(), b1.getAffSize(),
        b2.getX(), b2.getY(), b2.getAffSize()
    );
}

#endif