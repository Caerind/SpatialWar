#include "Chunk.hpp"
#include "../World.hpp"
#include "../../Lib/Aharos/Helper/Math.hpp"

Chunk::Chunk(sf::Vector2i coords)
: mCoords(coords)
{
    mSprite.setTexture(World::getResources().getTexture("spaceBackground"));
    mSprite.setTextureRect(sf::IntRect(lp::random(0,3) * 1024, 0, 1024, 1024));
    mSprite.setPosition(coords.x * 1024.f, coords.y * 1024.f);
}

sf::Vector2i Chunk::getCoords() const
{
    return mCoords;
}

sf::FloatRect Chunk::getBounds() const
{
    auto r = mSprite.getGlobalBounds();
    r.left += getPosition().x;
    r.top += getPosition().y;
    return r;
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
