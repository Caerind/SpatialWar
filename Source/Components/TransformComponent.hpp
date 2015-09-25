#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <SFML/Graphics/Transformable.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class TransformComponent : public ses::Component, public sf::Transformable
{
    public:
        TransformComponent();

        static std::string getId();
};

#endif // TRANSFORMCOMPONENT_HPP
