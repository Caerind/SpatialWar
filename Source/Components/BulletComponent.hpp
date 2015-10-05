#ifndef BULLETCOMPONENT_HPP
#define BULLETCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class BulletComponent : public ses::Component, public sf::Drawable
{
    public:
        BulletComponent();

        static std::string getId();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
};
#endif // BULLETCOMPONENT_HPP
