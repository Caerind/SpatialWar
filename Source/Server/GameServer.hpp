#ifndef SERVER_GAMESERVER_HPP
#define SERVER_GAMESERVER_HPP

#include "Server.hpp"
#include "World.hpp"

namespace srv
{

class GameServer : public Server
{
    public:
        GameServer();

    protected:
        void handlePacket(sf::Packet& packet, Peer& peer, bool& detectedTimeout);
        void update(sf::Time dt);
};

} // namespace srv

#endif // SERVER_GAMESERVER_HPP
