#ifndef ONLINEGAMESTATE_HPP
#define ONLINEGAMESTATE_HPP

#include "../../Lib/Aharos/Application/State.hpp"

#include "../Configuration.hpp"
#include "../Client/ClientEntityManager.hpp"

class OnlineGameState : public ah::State
{
    public:
        OnlineGameState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();

    private:
        ClientEntityManager mManager;
};

#endif // ONLINEGAMESTATE_HPP
