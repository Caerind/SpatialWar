#ifndef SERVER_PEER_HPP
#define SERVER_PEER_HPP

#include <memory>

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace srv
{

class Peer
{
    public:
        Peer();

        typedef std::unique_ptr<Peer> Ptr;

        sf::TcpSocket& getSocket();
        sf::Socket::Status receive(sf::Packet& packet);
        sf::Socket::Status send(sf::Packet& packet);

        unsigned int getId() const;
        sf::Time getLastPacketTime() const;
        bool isReady() const; // ready mean the player is linked to the server and can receive packets
        bool isConnected() const; // connected mean the player is authentified as a real player (he is playing)
        bool hasTimedOut() const;
        std::string getName() const;

        void setReady(bool ready);
        void setTimedOut(bool timedOut);
        void setName(std::string const& name);

    protected:
        static unsigned int mIdCounter;

        sf::TcpSocket mSocket;

        unsigned int mId;
        sf::Clock mLastPacketTime;
        bool mReady;
        bool mTimedOut;
        std::string mName;
};

} // namespace srv

#endif // SERVER_PEER_HPP
