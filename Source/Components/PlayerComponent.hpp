#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/View.hpp>

class PlayerComponent : public ses::Component
{
    public:
        PlayerComponent();

        static std::string getId();

        sf::View* getView();

    private:
        sf::View* mView;
};

#endif // PLAYERCOMPONENT_HPP
