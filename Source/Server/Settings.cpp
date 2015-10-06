#include "Settings.hpp"

namespace srv
{

Settings::Settings()
{
    if (!loadFromFile("Assets/Server/server.properties"))
    {
        createDefault();
        saveToFile("Assets/Server/server.properties");
    }
}

bool Settings::loadFromFile(std::string const& name)
{
    std::ifstream file(name);
    if (!file)
    {
        return false;
    }

    std::string line;
    while (std::getline(file,line))
    {
        if(line.size() > 0 && line[0] != '#')
        {
            size_t index = 0;
            while(std::isspace(line[index]))
                index++;
            const size_t beginKeyString = index;
            while(!std::isspace(line[index]) && line[index] != '=')
                index++;
            const std::string key = line.substr(beginKeyString, index - beginKeyString);
            while(std::isspace(line[index]) || line[index] == '=')
                index++;
            const std::string value = line.substr(index, line.size() - index);

            mSettings[key] = value;
        }
    }

    file.close();
    return true;
}

bool Settings::saveToFile(std::string const& name)
{
    std::ofstream file(name);
    if (!file)
    {
        return false;
    }

    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        file << itr->first << "=" << itr->second << std::endl;
    }

    file.close();
    return true;
}

void Settings::createDefault()
{
    mSettings["logfile"] = "server.log";
    mSettings["maxplayers"] = lp::to_string(10);
    mSettings["port"] = lp::to_string(4567);
}

std::string Settings::getString(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            return itr->second;
        }
    }
    return "";
}

int Settings::getInt(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            return lp::from_string<int>(itr->second);
        }
    }
    return 0;
}

float Settings::getFloat(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            return lp::from_string<float>(itr->second);
        }
    }
    return 0.f;
}

bool Settings::getBool(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            return (itr->second == "true") ? true : false;
        }
    }
    return false;
}

void Settings::set(std::string const& id, std::string const& value)
{
    mSettings[id] = value;
}

void Settings::set(std::string const& id, int value)
{
    mSettings[id] = lp::to_string(value);
}

void Settings::set(std::string const& id, float value)
{
    mSettings[id] = lp::to_string(value);
}

void Settings::set(std::string const& id, bool value)
{
    mSettings[id] = (value) ? "true" : "false";
}

} // namespace srv
