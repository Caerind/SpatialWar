#include "PlayerComponent.hpp"
#include "../World.hpp"

PlayerComponent::PlayerComponent()
: ses::Component()
, mView(nullptr)
{
    #ifdef SW_CLIENT
    mView = &World::getView();
    #endif // SW_CLIENT
}

std::string PlayerComponent::getId()
{
    return "PlayerComponent";
}

sf::View* PlayerComponent::getView()
{
    return mView;
}
