#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

#include <SFML/System/Time.hpp>

class MovementSystem : public ses::System
{
    public:
        MovementSystem(std::shared_ptr<ses::EntityManager> entityManager);

        static std::string getId();

        void update(sf::Time dt);
        void collision(sf::Int32 const& entityId);
        void handleCollision(sf::Int32 const& entity1, sf::Int32 const& entity2);

        void handlePacket(sf::Packet& packet);
};

#endif // MOVEMENTSYSTEM_HPP
