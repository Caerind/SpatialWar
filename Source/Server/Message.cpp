#include "Message.hpp"

namespace srv
{

Message::Message()
{
    //ctor
}

std::string Message::getEmitter() const
{
    return mEmitter;
}

std::string Message::getContent() const
{
    return mContent;
}

void Message::setEmitter(std::string const& emitter)
{
    mEmitter = emitter;
}

void Message::setContent(std::string const& content)
{
    mContent = content;
}

bool Message::isCommand() const
{
    return mContent.find("/") != 0;
}

} // namespace srv

sf::Packet& operator <<(sf::Packet& packet, const srv::Message& msg)
{
    return packet << msg.getEmitter() << msg.getContent();
}

sf::Packet& operator >>(sf::Packet& packet, srv::Message& msg)
{
    std::string e,c;
    packet >> e >> c;
    msg.setEmitter(e);
    msg.setContent(c);
    return packet;
}

