#ifndef PLAYERINPUTSYSTEM_HPP
#define PLAYERINPUTSYSTEM_HPP

#include <SFML/System/Time.hpp>

#include "../../Lib/EntitySystem/System.hpp"
#include "../../Lib/Aharos/Application/ActionTarget.hpp"
#include "../../Lib/Aharos/Application/Application.hpp"

#include "../Components.hpp"
#include "../Configuration.hpp"

class PlayerInputSystem : public ses::System, public ah::ActionTarget
{
    public:
        PlayerInputSystem(std::shared_ptr<ses::EntityManager> entityManager);

        static std::string getId();

        void update(sf::Time dt);

        void handlePacket(sf::Packet& packet);
};

#endif // PLAYERINPUTSYSTEM_HPP
