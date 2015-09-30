#ifndef BASECOMPONENT_HPP
#define BASECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include "../../Lib/Aharos/Helper/CollisionShape.hpp"

class BaseComponent : public ses::Component, public lp::CollisionShape
{
    public:
        BaseComponent();

        static std::string getId();

        float getLife() const;
        void setLife(float life);
        void inflige(float damage);
        void restore(float restore);
        bool isDead() const;

        float getMass() const;
        void setMass(float mass);

    private:
        float mLife;
        float mMass;
};

#endif // BASECOMPONENT_HPP
