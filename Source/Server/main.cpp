#include "CommandHandler.hpp"
#include "GameServer.hpp"

#include "../../Lib/Aharos/Application/Application.hpp"

int main()
{
    srv::GameServer server;

    srv::Settings& serverSettings = server.getSettings();

    ah::Application::instance().openLog(serverSettings.getString("logfile"));

    srv::CommandHandler command(server);
    std::string line;

    server.start();

    while (server.isRunning())
    {
        line.clear();
        std::getline(std::cin, line);
        command.handle(line);
    }

    return EXIT_SUCCESS;
}
