#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <vector>

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Thread.hpp>

#include "../../Lib/Aharos/Application/Application.hpp"

#include "PacketType.hpp"
#include "Peer.hpp"
#include "Settings.hpp"
#include "Message.hpp"

namespace srv
{

class Server
{
    public:
        Server();

        void start();
        void stop();
        bool isRunning() const;

        void sendToAll(sf::Packet& packet);
        void sendToPeer(sf::Packet& packet, unsigned int peerId);
        void sendToPeer(sf::Packet& packet, Peer& peer);

        Settings& getSettings();

    protected:
        void setListening(bool enable);

        void run();
        void update(sf::Time dt);

        void handlePackets();
        void handlePacket(sf::Packet& packet, Peer& peer, bool& detectedTimeout);

        void handleConnections();
        void handleDisconnections();

    protected:
        sf::Thread mThread;
        bool mRunning;

        sf::TcpListener mListener;
        bool mListeningState;

        Settings mSettings;

        std::size_t mMaxPlayers;
        std::size_t mPort;
        sf::Time mClientTimeoutTime;
        sf::Time mUpdateInterval;

        std::size_t mConnectedPlayers;

        std::vector<Peer::Ptr> mPeers;
};

} // namespace srv

#endif // SERVER_SERVER_HPP
