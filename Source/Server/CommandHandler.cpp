#include "CommandHandler.hpp"

namespace srv
{

CommandHandler::CommandHandler(Server& server)
: mServer(server)
{
}

CommandHandler::Arguments CommandHandler::splitArguments(std::string const& command)
{
    Arguments args;
    std::stringstream ss(command);
    std::string arg;
    while (std::getline(ss,arg,' '))
    {
        args.push_back(arg);
    }
    return args;
}

void CommandHandler::handle(std::string const& command)
{
    Arguments args = splitArguments(command);

    // Return if no arguments
    if (args.size() == 0)
    {
        return;
    }

    if (args[0] == "stop")
    {
        mServer.stop();
    }
}

} // namespace srv
