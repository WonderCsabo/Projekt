#include "MessageObject.h"

//deault constructor, general type, null message
MessageObject::MessageObject() : type(100), message("null") {}

MessageObject::MessageObject(const MessageObject& m)
{
    this->type = m.type;
    this->message = m.message;
}

//general message with the specified string
MessageObject::MessageObject(std::string message_) : type(100), message(message_) {}


//message with specified type and message string
MessageObject::MessageObject(unsigned short type_, std::string message_) : type(type_), message(message_) {}

std::string MessageObject::toString()
{
    std::stringstream ss;
    ss << type << " " << message;
    return ss.str();
}

MessageObject& MessageObject::operator=(const MessageObject& rhs)
{
    this->type = rhs.type;
    this->message = rhs.message;
    return *this;
}

//out operator for messageobject
std::ostream& operator<<(std::ostream& os, const MessageObject& obj)
{
    os << obj.type << ' ' << obj.message;
    return os;
}

//out operator for message obejct, it can be passed to a packet
sf::Packet& operator<<(sf::Packet& packet, const MessageObject& m)
{
    return packet << m.type << m.message;
}

//in operator for message object, it can be loaded from a packet
sf::Packet& operator>>(sf::Packet& packet, MessageObject& m)
{
    return packet >> m.type >> m.message;
}

bool operator==(const MessageObject& lhs, const MessageObject& rhs)
{
    return (lhs.type == rhs.type && lhs.message == rhs.message);
}