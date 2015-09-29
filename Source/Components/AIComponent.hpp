#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class AIComponent : public ses::Component
{
    public:
        AIComponent();

        static std::string getId();
};

#endif // AICOMPONENT_HPP
