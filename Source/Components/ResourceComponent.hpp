#ifndef RESOURCECOMPONENT_HPP
#define RESOURCECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class ResourceComponent : public ses::Component, public sf::Drawable
{
    public:
        ResourceComponent();

        static std::string getId();

        void setResourceId(int id);
        int getResourceId() const;

        void setAmount(float amount);
        float getAmount() const;

        void setDirection(sf::Vector2f direction);
        sf::Vector2f getDirection() const;

        void setSpeed(float speed);
        float getSpeed() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
        int mId;
        float mAmount;
        sf::Vector2f mDirection;
        float mSpeed;
};

#endif // RESOURCECOMPONENT_HPP
