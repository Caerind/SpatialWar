#include "OnlineGameState.hpp"

OnlineGameState::OnlineGameState(ah::StateManager& manager) : ah::State(manager), mManager(Configuration::getSocket())
{
    mType = OnlineGameState::getID();
}

std::string OnlineGameState::getID()
{
    return "OnlineGameState";
}

bool OnlineGameState::handleEvent(sf::Event const& event)
{
    //World::instance().handleEvent(event);
    return true;
}

bool OnlineGameState::update(sf::Time dt)
{
    //World::instance().update(dt);
    return true;
}

void OnlineGameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //World::instance().render(target);
}

void OnlineGameState::onActivate()
{
    //World::instance().initialize();
}

void OnlineGameState::onDeactivate()
{
    //World::instance().terminate();
}
