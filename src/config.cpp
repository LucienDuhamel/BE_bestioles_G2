#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Config::load(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur : impossible d'ouvrir " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Supprimer les commentaires inline
        size_t posComment = line.find("//");
        if (posComment != std::string::npos)
            line = line.substr(0, posComment);

        posComment = line.find('#');
        if (posComment != std::string::npos)
            line = line.substr(0, posComment);

        // Trim final pour retirer les espaces après suppression des commentaires
        auto trim = [](std::string& s) {
            while (!s.empty() && (s[0] == ' ' || s[0] == '\t'))
                s.erase(0, 1);
            while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r'))
                s.pop_back();
        };

        trim(line);

        if (line.empty())
            continue;

        // Recherche de la clé et de la valeur
        size_t pos = line.find(':');
        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        trim(key);
        trim(value);

        if (!key.empty())
            data[key] = value;
    }
}


int Config::getInt(const std::string& key, int defaultValue) const
{
    auto it = data.find(key);
    if (it == data.end())
        return defaultValue;
    std::cout << "Config::getInt: key=" << key << ", value=" << it->second << std::endl;
    return std::stoi(it->second);
}

double Config::getDouble(const std::string& key, double defaultValue) const
{
    auto it = data.find(key);
    if (it == data.end())
        return defaultValue;
    std::cout << "Config::getDouble: key=" << key << ", value=" << it->second << std::endl;
    return std::stod(it->second);
}

std::string Config::getString(const std::string& key, const std::string& defaultValue) const
{
    auto it = data.find(key);
    if (it == data.end())
        return defaultValue;
    std::cout << "Config::getString: key=" << key << ", value=" << it->second << std::endl;
    return it->second;
}
