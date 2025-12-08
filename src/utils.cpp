#include "utils.h"

double randomBetween(double a, double b) {
    static std::mt19937 gen(std::random_device{}());              // générateur statique
    std::uniform_real_distribution<double> dist(a, b);     
    return dist(gen);
}

std::unordered_map<std::string, std::string> loadJSONConfig(const std::string& filename) {
    std::unordered_map<std::string, std::string> config;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        // retirer espaces et virgules
        line.erase(remove_if(line.begin(), line.end(), [](char c){ return c == ' ' || c == ','; }), line.end());

        // ignorer accolades
        if (line.empty() || line == "{" || line == "}") continue;

        // trouver la clé et la valeur
        size_t colon = line.find(':');
        if (colon == std::string::npos) continue;

        std::string key = line.substr(0, colon);
        std::string value = line.substr(colon + 1);

        // retirer guillemets si string
        if (!value.empty() && value.front() == '"') value.erase(0,1);
        if (!value.empty() && value.back() == '"') value.pop_back();

        if (!key.empty() && key.front() == '"') key.erase(0,1);
        if (!key.empty() && key.back() == '"') key.pop_back();

        config[key] = value;
    }

    return config;
}

