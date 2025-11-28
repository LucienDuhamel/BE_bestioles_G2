#include "utils.h"


#include <random>

double randomBetween(double a, double b) {
    static std::mt19937 gen(std::random_device{}());              // générateur statique
    std::uniform_real_distribution<double> dist(a, b);     
    return dist(gen);
}
