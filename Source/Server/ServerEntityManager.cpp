#include "ServerEntityManager.hpp"

ServerEntityManager::ServerEntityManager()
: ses::EntityManager()
{
    mConnected = false;
    mSocket.setBlocking(false);

    setPrefab("Sprite",[&]() -> sf::Int32
    {
        sf::Int32 id = addEntity();
        //addComponent<SpriteComponent>(id);
        // Send Entity Addition
        {
            sf::Packet packet;
            packet << 50 << id;
            sendPacket(packet);
        }
        // Send Sprite Component Addition
        {
            sf::Packet packet;
            packet << 51 << id;
            sendPacket(packet);
        }
        return id;
    });
}

void ServerEntityManager::sendPacket(sf::Packet& packet)
{
    mSocket.send(packet);
}

void ServerEntityManager::handlePackets()
{
    while (mRunning)
    {
        if (mConnected)
        {
            sf::Packet m;
            while (mSocket.receive(m) == sf::Socket::Done && mSystems != nullptr)
            {
                handlePacket(m);
            }
        }
        else
        {
            if (mListener.listen(53000) == sf::Socket::Done)
            {
                std::cout << "Server :: Port ouvert" << std::endl;
                if (mListener.accept(mSocket) == sf::Socket::Done)
                {
                    std::cout << "Server :: Connexion ok" << std::endl;
                    mConnected = true;
                }
                else
                {
                    std::cout << "Server :: Client non accepte" << std::endl;
                }
            }
            else
            {
                std::cout << "Server :: Port non ouvert" << std::endl;
            }
        }
    }
}

void ServerEntityManager::handlePacket(sf::Packet& packet)
{
    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        default: break;
    }
}

