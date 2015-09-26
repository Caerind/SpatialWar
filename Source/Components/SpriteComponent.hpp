#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class SpriteComponent : public ses::Component, public sf::Sprite
{
    public:
        SpriteComponent();
        SpriteComponent(sf::Texture const& texture);
        SpriteComponent(sf::Texture const& texture, sf::IntRect const& textureRect);
        SpriteComponent(std::string const& textureId);
        SpriteComponent(std::string const& textureId, sf::IntRect const& textureRect);

        static std::string getId();
};

#endif // SPRITECOMPONENT_HPP
