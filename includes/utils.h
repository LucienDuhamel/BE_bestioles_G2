#ifndef UTILS
#define UTILS

#include "Bestiole.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <random>

using namespace std;

#include <random>

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

    return std::atan2(-dy, dx); // lorsque l'axe des y est vers le bas
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
        return 0.0; // or throw an exception if preferred
    }

    double sum = 0.0;
    for (const auto& value : values) {
        sum += static_cast<double>(value);
    }
    return sum / static_cast<double>(values.size());
};

#endif