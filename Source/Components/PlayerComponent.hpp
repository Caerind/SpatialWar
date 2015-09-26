#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class PlayerComponent : public ses::Component
{
    public:
        PlayerComponent();

        static std::string getId();
};

#endif // PLAYERCOMPONENT_HPP
