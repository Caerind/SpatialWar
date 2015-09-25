#include "../Lib/Aharos/Application/Application.hpp"

#include "States/GameState.hpp"
#include "States/OnlineGameState.hpp"

#include "Configuration.hpp"

int main()
{
    // Load Application
    ah::Application::instance().loadFont("Coolveticca","Assets/Fonts/Coolveticca.ttf");
    ah::Application::instance().setFont(ah::Application::instance().getFont("Coolveticca"));
    ah::Application::instance().showDebugScreen(true);
    ah::Application::instance().useConsole(true);

    // Window Config
    ah::Application::instance().create(sf::VideoMode(800,600),"Rucks");
    ah::Application::instance().setIcon("Assets/Textures/icon.png");
    ah::Application::instance().setMouseCursorTexture("Assets/Textures/cursor.png");
    ah::Application::instance().useCustomMouseCursor();

    // Register States
    ah::Application::instance().registerState<GameState>(GameState::getID());
    ah::Application::instance().registerState<OnlineGameState>(OnlineGameState::getID());

    // Run
    ah::Application::instance().pushState(GameState::getID());
    ah::Application::instance().run();

    return EXIT_SUCCESS;
}
