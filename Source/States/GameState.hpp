#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../../Lib/Aharos/Application/State.hpp"
#include "../../Lib/Aharos/Application/Application.hpp"

#include "../Configuration.hpp"
#include "../World.hpp"

#include "../EntityManager.hpp"

class GameState : public ah::State
{
    public:
        GameState(ah::StateManager& manager);
        ~GameState();

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();
};

#endif // GAMESTATE_HPP
