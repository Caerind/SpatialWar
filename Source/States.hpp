#ifndef STATES_HPP_INCLUDED
#define STATES_HPP_INCLUDED

#include "States/LoadingState.hpp"
#include "States/GameState.hpp"

#include "../Lib/Aharos/Application/Application.hpp"

namespace states
{

void registerStates()
{
    ah::Application::instance().registerState<LoadingState>();
    ah::Application::instance().registerState<GameState>();
}

}

#endif // STATES_HPP_INCLUDED
