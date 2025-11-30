// Config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class Config {
private:
    std::unordered_map<std::string, std::string> data;
    Config() {}  // constructeur privé
public:
    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    void load(const std::string& filename);
    int getInt(const std::string& key, int defaultValue = 0) const;
    double getDouble(const std::string& key, double defaultValue = 0.0) const;
    std::string getString(const std::string& key, const std::string& defaultValue = "") const;
};


#endif // CONFIG_H