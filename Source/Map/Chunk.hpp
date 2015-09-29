#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Chunk : public sf::Drawable, sf::Transformable
{
    public:
        Chunk(sf::Vector2i coords);

        sf::Vector2i getCoords() const;
        sf::FloatRect getBounds() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Vector2i mCoords;
        sf::Sprite mSprite;
};

#endif // CHUNK_HPP
