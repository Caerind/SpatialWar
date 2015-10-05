#include "../Lib/Aharos/Application/Application.hpp"

#include "States.hpp"

int main()
{
    // Load Application
    ah::Application::instance().loadFont("Coolveticca","Assets/Fonts/Coolveticca.ttf");
    ah::Application::instance().setFont(ah::Application::instance().getFont("Coolveticca"));
    ah::Application::instance().showDebugScreen(true);
    ah::Application::instance().useConsole(true);

    // Window Config
    ah::Application::instance().create(sf::VideoMode(800,600),"SpatialWar");
    ah::Application::instance().setIcon("Assets/Textures/icon.png");
    ah::Application::instance().setMouseCursorTexture("Assets/Textures/cursor.png");
    ah::Application::instance().setMouseCursorTextureRect(sf::IntRect(34,34,34,34));
    ah::Application::instance().useCustomMouseCursor();

    // Load Some Resources
    ah::Application::instance().loadFont("future","Assets/Fonts/future.ttf");
    ah::Application::instance().loadFont("future_thin","Assets/Fonts/future_thin.ttf");

    // Register States
    ah::Application::instance().registerState<GameState>();
    ah::Application::instance().registerState<LoadingState>();

    // Run
    ah::Application::instance().pushState(LoadingState::getID());
    ah::Application::instance().runMaxFps();

    return EXIT_SUCCESS;
}
