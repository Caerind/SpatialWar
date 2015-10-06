#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "../Lib/Aharos/Application/ActionTarget.hpp"

#include <SFML/Network/IpAddress.hpp>

class Configuration
{
    public:
        static ah::ActionTarget::ActionMapPtr getPlayerInput();
        static sf::IpAddress& getServerAddress();
        static unsigned short& getServerPort();

    private:
        Configuration();
        ~Configuration();

        static Configuration mInstance;

        ah::ActionTarget::ActionMapPtr mPlayerInput;
        sf::IpAddress mAddress;
        unsigned short mPort;
};

#endif // CONFIGURATION_HPP
