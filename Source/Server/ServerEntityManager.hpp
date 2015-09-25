#ifndef SERVERENTITYMANAGER_HPP
#define SERVERENTITYMANAGER_HPP

#include <iostream>

#include <SFML/Network.hpp>

#include "../../Lib/Aharos/Application/Application.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"

#include "Components.hpp"
#include "Systems.hpp"

class ServerEntityManager : public ses::EntityManager
{
    public:
        ServerEntityManager();

        void sendPacket(sf::Packet& packet);
        void handlePackets();
        void handlePacket(sf::Packet& packet);

    private:
        sf::TcpListener mListener;
        sf::TcpSocket mSocket;
        bool mConnected;
};

#endif // SERVERENTITYMANAGER_HPP
