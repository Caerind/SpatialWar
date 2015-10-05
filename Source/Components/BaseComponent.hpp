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
        float getLifeMax() const;
        void setLifeMax(float lifeMax);
        bool inflige(float damage);
        bool restore(float restore);
        void restoreFullLife();
        bool isFullLife() const;
        bool isDead() const;

        float getMass() const;
        void setMass(float mass);

        float getSpeed() const;
        void setSpeed(float speed);

    private:
        float mLife;
        float mLifeMax;
        float mMass;
        float mSpeed;
};

#endif // BASECOMPONENT_HPP
