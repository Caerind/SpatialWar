#ifndef CLIENTENTITYMANAGER_HPP
#define CLIENTENTITYMANAGER_HPP

#include <iostream>

#include <SFML/Network.hpp>

#include "../../Lib/Aharos/Application/Application.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"

#include "Components.hpp"
#include "Systems.hpp"

class ClientEntityManager : public ses::EntityManager
{
    public:
        ClientEntityManager(sf::TcpSocket& socket);

        void sendPacket(sf::Packet& packet);
        void handlePackets();
        void handlePacket(sf::Packet& packet); // Maybe should inherrit from EntityManager ? To have the solo packet already done

    private:
        sf::TcpSocket& mSocket;
        bool mConnected;
};

#endif // CLIENTENTITYMANAGER_HPP
