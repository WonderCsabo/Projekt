#include "Client.h"
#include "../Util/DebugWindow.h"

/**
* constructs a client with the given port and ip address,
* sets the default variables, and starts the input thread,
* and also the manager thread for the client
* @param unsigned int port
* @param IpAddress IP address
*/
Client::Client(unsigned int port_, sf::IpAddress addr_, std::string nickname_) : address(addr_), port(port_), isRunning(true), nickname(nickname_)
{
	status = server.connect(address, port);
	if (status == sf::Socket::Done)
	{
		MessageObject hi(MessageObject::CONN, nickname);
		send(hi);
		std::cout << hi;
		launch();
	}
}

/**
* launches the servers main thread
*/
void Client::launch()
{
	manager = new sf::Thread(&Client::manageClient, this);
	manager->launch();
}

/**
* sends a message event (eg: action) to the server, its type depends on the event actions
* @param the current event
*/
void Client::sendEventMessage(sf::Event& ev)
{
	std::stringstream ss;
	if (ev.type == ev.MouseButtonReleased)
	{
		ss << ev.mouseButton.x << " " << ev.mouseButton.y;
		if (ev.mouseButton.button == sf::Mouse::Right)
		{
			send(MessageObject::ACTION, "user shot/moved to " + ss.str());
		}
		else if (ev.mouseButton.button == sf::Mouse::Left)
		{
			send(MessageObject::MVMNT, "user clicked at: " + ss.str());
		}
	}

}

/**
* manages the client, recieves the messages from the server and pushes them to the message queue
*/
void Client::manageClient()
{
	while(isRunning)
	{
		sf::sleep(sf::milliseconds(10));
		MessageObject m = recieve();
		messages.push_back(m);
		if (m.type == MessageObject::CMD && m.message == "shut")
		{
			isRunning = false;
			shutDown();
		}
	}
}

/**
* true, if the connection to the server was successful, else false
* @retrun bool
*/
bool Client::isConnected()
{
	return (status==sf::Socket::Done);
}

/**
* @return the nickname
*/
std::string Client::getNickname()
{
	return nickname;
}

/**
* returns the client's socket
* @return TcpSocket
*/
sf::TcpSocket* Client::getSocket()
{
	return &server;
}

/**
* sends a general message
* @param string
*/
void Client::send(std::string message)
{
	MessageObject m(100, message);
	send(m);
}

/**
* sends a specific message
* @param MessageObject
*/
void Client::send(MessageObject message)
{
	sf::Packet packet;
	packet << message;
	server.send(packet);
}

/**
* sends a message constructed by the given type and message string
* @param unsigned short
* @param string
*/
void Client::send(unsigned short type, std::string message)
{
	MessageObject m(type, message);
	send(m);
}

/**
* recieves a MessageObject from the server
* @return MessageObject
*/
MessageObject Client::recieve()
{
	MessageObject m;
	sf::Packet packet;
	server.receive(packet);
	packet >> m;
	return m;
}

/**
* gets the last message from the message queue
* @return MessageObject
*/
MessageObject Client::getLastMessage()
{
	if (messages.size()!=0)
	{
		MessageObject m = messages.front();
		messages.pop_front();
		return m;
	}
	else
	{
		MessageObject m;
		return m;
	}
}

/**
* shuts down the client, and sends a disconnect message to the server
*/
void Client::shutDown()
{
	//std::cout << "Connection closed\nPress Enter to exit";
	send(MessageObject::CMD, "DISC");
	isRunning = false;
	server.disconnect();
}

/**
* destructor, if the client is still running, shuts it down
*/
Client::~Client()
{
	if (isRunning)
		shutDown();
	delete manager;
}
