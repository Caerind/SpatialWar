#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "../../Lib/Aharos/Application/State.hpp"
#include "../../Lib/Aharos/Application/Application.hpp"

#include "../World.hpp"

#include "GameState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>

#include "../../Lib/Aharos/SimpleGui/Timer.hpp"

class LoadingState : public ah::State
{
    public:
        LoadingState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Thread mThread;
        sf::Clock mClock;

        sf::RectangleShape mBackground;
        sf::Text mText;

        sg::Timer mTimer;
};

#endif // LOADINGSTATE_HPP
