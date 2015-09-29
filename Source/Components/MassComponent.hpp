#ifndef MASSCOMPONENT_HPP
#define MASSCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class MassComponent : public ses::Component
{
    public:
        MassComponent();

        static std::string getId();

        float getMass() const;
        void setMass(float mass);

    private:
        float mMass;
};

#endif // MASSCOMPONENT_HPP
