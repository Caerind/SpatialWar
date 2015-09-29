#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/View.hpp>

#include "EntityManager.hpp"
#include "Client/ClientEntityManager.hpp"
#include "../Lib/EntitySystem/SystemManager.hpp"

#include "Configuration.hpp"
#include "Space.hpp"

#include "Systems.hpp"
#include "Components.hpp"

class World
{
    public:
        static void init(bool onlineMode, bool server);
        static void terminate();

        static void handleEvent(sf::Event const& event);
        static void update(sf::Time dt);
        static void render(sf::RenderTarget& target, sf::RenderStates states);

        static bool isOnline();
        static bool isServer();
        //static ses::EntityManager& getEntityManager();
        //static ses::SystemManager& getSystems();
        static ah::ResourceHolder& getResources();
        static sf::View& getView();
        static Space& getSpace();

    private:
        World();
        ~World();

        static World mInstance;

        bool mOnlineMode;
        bool mServer;
        ses::EntityManager::Ptr mEntities;
        ses::SystemManager mSystems;
        ah::ResourceHolder mResources;
        sf::View mView;
        Space mSpace;
};

#endif // WORLD_HPP
