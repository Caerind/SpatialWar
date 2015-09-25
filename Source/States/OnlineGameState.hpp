#ifndef ONLINEGAMESTATE_HPP
#define ONLINEGAMESTATE_HPP

#include "../../Lib/Aharos/Application/State.hpp"
#include "../../Lib/Aharos/Application/Application.hpp"

#include "../Configuration.hpp"
#include "../World.hpp"

#include "../Client/ClientEntityManager.hpp"

class OnlineGameState : public ah::State
{
    public:
        OnlineGameState(ah::StateManager& manager);
        ~OnlineGameState();

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();
};

#endif // ONLINEGAMESTATE_HPP
