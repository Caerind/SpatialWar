#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "../Components.hpp"

class RenderSystem : public ses::System
{
    public:
        RenderSystem(std::shared_ptr<ses::EntityManager> entityManager);

        static std::string getId();

        void render(sf::RenderTarget& target, sf::RenderStates states);

        void handlePacket(sf::Packet& packet);
};

#endif // RENDERSYSTEM_HPP
