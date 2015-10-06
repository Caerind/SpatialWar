#ifndef SERVER_SETTINGS_HPP
#define SERVER_SETTINGS_HPP

#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include <iostream>

#include "../../Lib/Aharos/Helper/String.hpp"

namespace srv
{

class Settings
{
    public:
        Settings();

        bool loadFromFile(std::string const& name);
        bool saveToFile(std::string const& name);
        void createDefault();

        std::string getString(std::string const& id);
        int getInt(std::string const& id);
        float getFloat(std::string const& id);
        bool getBool(std::string const& id);

        void set(std::string const& id, std::string const& value);
        void set(std::string const& id, int value);
        void set(std::string const& id, float value);
        void set(std::string const& id, bool value);

    protected:
        std::map<std::string,std::string> mSettings;
};

} // namespace srv

#endif // SERVER_SETTINGS_HPP
