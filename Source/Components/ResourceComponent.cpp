#include "ResourceComponent.hpp"
#include "../World.hpp"

ResourceComponent::ResourceComponent()
: ses::Component()
{
    // TODO : mSprite.setTexture(World::getResources().getTexture("resources"));
}

std::string ResourceComponent::getId()
{
    return "ResourceComponent";
}

void ResourceComponent::setResourceId(int id)
{
    mId = id;
}

int ResourceComponent::getResourceId() const
{
    return mId;
}

void ResourceComponent::setAmount(float amount)
{
    mAmount = amount;
}

float ResourceComponent::getAmount() const
{
    return mAmount;
}

void ResourceComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}
