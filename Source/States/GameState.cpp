#include "GameState.hpp"

GameState::GameState(ah::StateManager& manager) : ah::State(manager)
{
    mType = GameState::getID();
    World::init(false);
}

GameState::~GameState()
{
    World::terminate();
}

std::string GameState::getID()
{
    return "GameState";
}

bool GameState::handleEvent(sf::Event const& event)
{
    World::handleEvent(event);
    return true;
}

bool GameState::update(sf::Time dt)
{
    World::update(dt);
    return true;
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    World::render(target,states);
}

void GameState::onActivate()
{
}

void GameState::onDeactivate()
{
}
