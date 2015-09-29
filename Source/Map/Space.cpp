#include "Space.hpp"
#include "../World.hpp"

Space::Space()
{
}

void Space::update(sf::View const& view)
{
    // Remove Old Chunks
    sf::FloatRect viewRect = sf::FloatRect(view.getCenter() - 1.5f * view.getSize(), 3.f * view.getSize());
    for (std::size_t i = 0; i < mChunks.size(); i++)
    {
        if (!viewRect.intersects(mChunks[i].getBounds()))
        {
            mChunks.erase(i + mChunks.begin());
        }
    }

    // Load New Chunks
    sf::Vector2f viewTL = view.getCenter() - view.getSize();
    sf::Vector2f viewBR = view.getCenter() + view.getSize();
    sf::Vector2i coords;
    sf::Vector2i b = sf::Vector2i(viewTL.x / 1024, viewTL.y / 1024) - sf::Vector2i(1,1);
    sf::Vector2i e = sf::Vector2i(viewBR.x / 1024, viewBR.y / 1024) + sf::Vector2i(1,1);
    for (coords.x = b.x; coords.x <= e.x; coords.x++)
    {
        for (coords.y = b.y; coords.y <= e.y; coords.y++)
        {
            if (!isChunkLoaded(coords))
            {
                mChunks.emplace_back(coords);
            }
        }
    }

    // Animations
}

void Space::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (std::size_t i = 0; i < mChunks.size(); i++)
    {
        target.draw(mChunks[i],states);
    }
}

void Space::clear()
{
    mChunks.clear();
}

std::size_t Space::size() const
{
    return mChunks.size();
}

bool Space::isChunkLoaded(sf::Vector2i coords)
{
    for (std::size_t i = 0; i < mChunks.size(); i++)
    {
        if (mChunks[i].getCoords() == coords)
        {
            return true;
        }
    }
    return false;
}

