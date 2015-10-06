#ifndef SERVER_WORLD_HPP
#define SERVER_WORLD_HPP

#include <SFML/System/Time.hpp>

#include "EntityManager.hpp"
#include "../../Lib/EntitySystem/SystemManager.hpp"

#include "Systems.hpp"
#include "Components.hpp"

namespace srv
{

class World
{
    public:
        static void init();
        static void terminate();

        static void update(sf::Time dt);

        static ses::EntityManager& getEntities();
        static ses::SystemManager& getSystems();

    private:
        World();
        ~World();

        static World mInstance;

        ses::EntityManager::Ptr mEntities;
        ses::SystemManager mSystems;
};

} // namespace srv

#endif // SERVER_WORLD_HPP
