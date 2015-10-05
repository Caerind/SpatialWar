#ifndef SHIPCOMPONENT_HPP
#define SHIPCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class ShipComponent : public ses::Component, public sf::Drawable
{
    public:
        ShipComponent();

        static std::string getId();

        bool isStationary() const;
        void setStationary(bool stationary);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setMotorId(int motorId);
        int getMotorId() const;

        void setArmorId(int armorId);
        int getArmorId() const;

        void setGunId(int gunId);
        int getGunId() const;

    private:
        sf::Sprite mSprite;
        bool mStationary;

        int mMotorId;
        int mArmorId;
        int mGunId;
};

#endif // SHIP_HPP
