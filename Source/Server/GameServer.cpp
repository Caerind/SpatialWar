#include "GameServer.hpp"

namespace srv
{

GameServer::GameServer()
: Server()
{
}

void GameServer::handlePacket(sf::Packet& packet, Peer& peer, bool& detectedTimeout)
{

}

void GameServer::update(sf::Time dt)
{
    World::update(dt);
}

} // namespace srv
