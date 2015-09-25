#include "EntityManager.hpp"

EntityManager::EntityManager()
: ses::EntityManager()
{
}

void EntityManager::handlePacket(sf::Packet& packet)
{
    int eventId;
    packet >> eventId;
    switch (eventId)
    {
        default: break;
    }
}

