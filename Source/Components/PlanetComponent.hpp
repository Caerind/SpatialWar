#ifndef PLANETCOMPONENT_HPP
#define PLANETCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class PlanetComponent : public ses::Component, public sf::Drawable
{
    public:
        PlanetComponent();

        static std::string getId();

        enum Type
        {
            Planet,
            Sun,
            Moon,
        };

        Type getType() const;
        void setType(Type type);

        float getRadius() const;
        void setRadius(float radius);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::CircleShape& getShape();

    private:
        sf::CircleShape mShape;
        float mRadius;
        Type mType;
};

#endif // PLANETCOMPONENT_HPP
