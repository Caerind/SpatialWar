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
        enum Type
        {
            Planet,
            Sun,
            Moon,
        };

        PlanetComponent(Type type = Type::Planet);

        static std::string getId();


        Type getType() const;
        void setType(Type type);

        float getRadius() const;
        void setRadius(float radius);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::CircleShape& getShape();

    private:
        Type mType;
        sf::CircleShape mShape;
};

#endif // PLANETCOMPONENT_HPP
