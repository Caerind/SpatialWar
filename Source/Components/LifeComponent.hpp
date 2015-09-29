#ifndef LIFECOMPONENT_HPP
#define LIFECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class LifeComponent : public ses::Component
{
    public:
        LifeComponent();

        static std::string getId();

        float getLife() const;
        void setLife(float life);

    private:
        float mLife;
};

#endif // LIFECOMPONENT_HPP
