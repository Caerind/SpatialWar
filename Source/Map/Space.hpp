#ifndef SPACE_HPP
#define SPACE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Chunk.hpp"

class Space : public sf::Drawable
{
    public:
        Space();

        void update(sf::View const& view);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void clear();
        std::size_t size() const;

        bool isChunkLoaded(sf::Vector2i coords);

    private:
        std::vector<Chunk> mChunks;
};

#endif // SPACE_HPP
