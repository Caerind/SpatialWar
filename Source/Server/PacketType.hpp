#ifndef PACKETTYPE_HPP_INCLUDED
#define PACKETTYPE_HPP_INCLUDED

namespace Packet
{
    enum Type
    {
        None = 0,
        // Server To Client
        ClientJoined,
        ClientLeft,
        ServerStopped,
        ServerMessage,


        // Client To Server
        Login,
        Disconnect,
        ClientMessage,

    };
}


#endif // PACKETTYPE_HPP_INCLUDED
