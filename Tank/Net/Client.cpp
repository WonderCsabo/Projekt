#include "Client.h"

/**
* constructs a client with the given port and ip address, 
* sets the default variables, and starts the input thread, 
* and also the manager thread for the client
* @param unsigned int port
* @param IpAddress IP address
*/
Client::Client(unsigned int port_, sf::IpAddress addr_, std::string nickname) : port(port_), address(addr_),
	isRunning(true), canRemove(false)/*, input(&Client::getInput, this)*/
{
	server.connect(address, port);
	MessageObject hi(MessageObject::MESSAGES::CONN, nickname);
	send(hi);
	//input.launch();
	//launch();
}

/*void Client::launch()
{
	sf::Thread manager(&Client::manageClient, this);

	manager.launch();
}*/

void Client::sendEventMessage(sf::Event& ev)
{
	std::stringstream ss;
	std::string buf = "";
	if (ev.mouseButton.button == sf::Mouse::Button::Left && ev.type == ev.MouseButtonPressed) {
		ss << ev.mouseButton.x << " " << ev.mouseButton.y;
		std::getline(ss, buf);
	}
	if (buf!="")
		send(MessageObject::MESSAGES::MVMNT, "user clicked at: " + buf);
}

/**
* manages the client, recieves and displays the messages from the server
*/
void Client::manageClient()
{
	while(isRunning)
	{
		MessageObject m = recieve();
		//std::cout << "server> " << m << std::endl;
		if (m.type == MessageObject::MESSAGES::CMD && m.message == "shut")
			shutDown();
	}
}

/**
* gets input from console, and sends it to the server
* this method runs in its own thread
*/
void Client::getInput()
{
	while (isRunning)
	{
		std::string in;
		getline(std::cin, in);
		if (in=="quit")
			shutDown();
		else if (in!="")
		{
			MessageObject m(100, in);
			send(m);
		}
	}
}

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
	sf::Packet packet;
	MessageObject m(100, message);
	packet << m;
	server.send(packet);
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
	sf::Packet packet;
	MessageObject m(type, message);
	packet << m;
	server.send(packet);
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
* shuts down the client, and sends a disconnect message to the server
*/
void Client::shutDown()
{
	//std::cout << "Connection closed\nPress Enter to exit";
	send(MessageObject::MESSAGES::CMD, "DISC");
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
}