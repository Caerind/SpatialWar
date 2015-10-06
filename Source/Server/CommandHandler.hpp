#ifndef SERVER_COMMANDHANDLER_HPP
#define SERVER_COMMANDHANDLER_HPP

#include <iostream>
#include <sstream>

#include "Server.hpp"

namespace srv
{

class CommandHandler
{
    public:
        CommandHandler(Server& server);

        friend Server;

    protected:
        typedef std::vector<std::string> Arguments;
        static Arguments splitArguments(std::string const& command);

    public:
        void handle(std::string const& command);

    protected:
        Server& mServer;
};

} // namespace srv

#endif // SERVER_COMMANDHANDLER_HPP
