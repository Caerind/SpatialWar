#include "OnlineGameState.hpp"

OnlineGameState::OnlineGameState(ah::StateManager& manager) : ah::State(manager)
{
    mType = OnlineGameState::getID();
    World::init(true);
}

OnlineGameState::~OnlineGameState()
{
    World::terminate();
}

std::string OnlineGameState::getID()
{
    return "OnlineGameState";
}

bool OnlineGameState::handleEvent(sf::Event const& event)
{
    World::handleEvent(event);
    return true;
}

bool OnlineGameState::update(sf::Time dt)
{
    World::update(dt);
    return true;
}

void OnlineGameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    World::render(target,states);
}

void OnlineGameState::onActivate()
{
}

void OnlineGameState::onDeactivate()
{
}
