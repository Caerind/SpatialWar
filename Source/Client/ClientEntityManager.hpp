#ifndef CLIENTENTITYMANAGER_HPP
#define CLIENTENTITYMANAGER_HPP

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

#include "../EntityManager.hpp"
#include "../Components.hpp"
#include "../Systems.hpp"

class ClientEntityManager : public EntityManager
{
    public:
        ClientEntityManager(sf::TcpSocket& socket);

        void sendPacket(sf::Packet& packet);
        void handlePackets();
        void handlePacket(sf::Packet& packet);

    private:
        sf::TcpSocket& mSocket;
        bool mConnected;
};

#endif // CLIENTENTITYMANAGER_HPP
