#include "GameServer.hpp"

namespace srv
{

GameServer::GameServer() : Server()
{
}

void GameServer::handlePacket(sf::Packet& packet, Peer& peer, bool& detectedTimeout)
{
    sf::Int32 packetType;
    packet >> packetType;

    switch (packetType)
    {
        case Packet::Login:
        {
            std::string username, password;
            packet >> username >> password;

            if (true)
            {
                peer.setName(username);

                ah::Application::instance() << "[Server] " + username + " joined the game";

                {
                    sf::Packet newPacket;
                    newPacket << Packet::ClientJoined << username;
                    sendToAll(newPacket);
                }

                std::vector<sf::Packet> packets;
                // packets loading
                for (std::size_t i = 0; i < packets.size(); i++)
                {
                    sendToPeer(packets[i],peer);
                }
            }
        } break;

        case Packet::Disconnect:
        {
            peer.setTimedOut(true);
            detectedTimeout = true;
        } break;

        case Packet::ClientMessage:
        {
            Message rMsg;
            packet >> rMsg;

            if (rMsg.isCommand())
            {
                // check permissions for the command
                // do the command

                Message msg;

                sf::Packet newPacket;
                newPacket << Packet::ServerMessage << msg;
                sendToPeer(newPacket,peer);
            }
            else if (!rMsg.isCommand())
            {
                sf::Packet newPacket;
                newPacket << Packet::ServerMessage << rMsg;
                sendToAll(newPacket);

                ah::Application::instance() << rMsg.getEmitter() + " : " + rMsg.getContent();
            }
        }

        default: break;
    }
}

void GameServer::update(sf::Time dt)
{
    World::update(dt);
}

} // namespace srv
