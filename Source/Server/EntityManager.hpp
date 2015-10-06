#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <iostream>

#include "../../Lib/Aharos/Application/Application.hpp"
#include "../../Lib/EntitySystem/EntityManager.hpp"

#include "Components.hpp"
#include "Systems.hpp"

class EntityManager : public ses::EntityManager
{
    public:
        EntityManager();

        virtual void handlePacket(sf::Packet& packet);
};

#endif // ENTITYMANAGER_HPP
