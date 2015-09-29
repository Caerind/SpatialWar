#include "AIComponent.hpp"

AIComponent::AIComponent()
: ses::Component()
{
}

std::string AIComponent::getId()
{
    return "AIComponent";
}
