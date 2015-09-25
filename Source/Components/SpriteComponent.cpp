#include "SpriteComponent.hpp"
#include "../World.hpp"

SpriteComponent::SpriteComponent()
: ses::Component()
, sf::Sprite()
{
}

SpriteComponent::SpriteComponent(sf::Texture const& texture)
: ses::Component()
, sf::Sprite(texture)
{
}

SpriteComponent::SpriteComponent(sf::Texture const& texture, sf::IntRect const& textureRect)
: ses::Component()
, sf::Sprite(texture,textureRect)
{
}

SpriteComponent::SpriteComponent(std::string const& textureId)
: ses::Component()
, sf::Sprite()
{
    if (World::getResources().isTextureLoaded(textureId))
    {
        setTexture(World::getResources().getTexture(textureId));
    }
}

SpriteComponent::SpriteComponent(std::string const& textureId, sf::IntRect const& textureRect)
: ses::Component()
, sf::Sprite()
{
    if (World::getResources().isTextureLoaded(textureId))
    {
        setTexture(World::getResources().getTexture(textureId));
        setTextureRect(textureRect);
    }
}

std::string SpriteComponent::getId()
{
    return "SpriteComponent";
}
