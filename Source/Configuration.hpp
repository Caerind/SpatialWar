#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "../Lib/Aharos/Application/ActionTarget.hpp"
#include <string>
#include <SFML/Network/IpAddress.hpp>

class Configuration
{
    public:
        static ah::ActionTarget::ActionMapPtr getPlayerInput();
        static sf::IpAddress getServerAddress();
        static unsigned short getServerPort();

        static void setUsername(std::string const& username);
        static void setPassword(std::string const& password);
        static std::string getUsername();
        static std::string getPassword();

    private:
        Configuration();
        ~Configuration();

        static Configuration mInstance;

        ah::ActionTarget::ActionMapPtr mPlayerInput;
        sf::IpAddress mAddress;
        unsigned short mPort;
        std::string mUsername;
        std::string mPassword;
};

#endif // CONFIGURATION_HPP
