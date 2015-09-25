#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <SFML/Network/TcpSocket.hpp>

#include "../Lib/Aharos/Application/ActionTarget.hpp"

class Configuration
{
    public:
        static ah::ActionTarget::ActionMapPtr getPlayerInput();
        static sf::TcpSocket& getSocket();

    private:
        Configuration();
        ~Configuration();

        static Configuration mInstance;

        ah::ActionTarget::ActionMapPtr mPlayerInput;
        sf::TcpSocket mSocket;
};

#endif // CONFIGURATION_HPP
