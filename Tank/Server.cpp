#include "Server.h"

/**
* constructor
* server starts listening on the specified port
* also starts the thread for user input and starts waiting for clients
*/
Server::Server(unsigned int port_) : port(port_), input(&Server::getInput, this)
{
	std::cout << "Server started\nListening on port " << port << std::endl;
	std::cout << "public ip address: " << sf::IpAddress::getPublicAddress().toString() << std::endl
			  << "local ip address " << sf::IpAddress::getLocalAddress() << std::endl;
	listener.listen(port);
	selector.add(listener);
	isRunning = true;
	sf::Thread thread(&Server::waitForClients, this);
	thread.launch();
	input.launch();
}

/**
* wating for clients, this method runs in its own thread
* if a client connects, sends a welcome message
* if a client sends a message, displays it
* if a client disconnects, remove it from the clients
*/
void Server::waitForClients()
{
	while(isRunning)
	{
		if (selector.wait())
		{
			if (selector.isReady(listener))
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					std::cout << "client connected " << client->getRemoteAddress() << std::endl;
					std::cout << "client> "; // << recieve(*client) << std::endl;
					MessageObject m = recieve(*client);
					std::cout << m << std::endl;
					send("I'm not the server You're looking for...", *client);
					clients.push_back(client);
					cms.push_back(new ClientManager(client, m.message));
					selector.add(*client);
				}
			}
			else
			{
				sf::TcpSocket* toRemove = 0;
				ClientManager* managerToRemove;
				//for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it!=clients.end(); ++it)
				for (std::list<ClientManager*>::iterator it = cms.begin(); it!=cms.end(); ++it)
				{
					//sf::TcpSocket& client = **it;
					ClientManager& cm = **it;
					sf::TcpSocket& client = * cm.getSocket();
					if (selector.isReady(client))
					{
						MessageObject msg;
						sf::Packet packet;
						sf::TcpSocket::Status status = client.receive(packet);
						packet >> msg;
						
						if (status == sf::Socket::Done) {
							std::cout << "client> " << msg << std::endl;
							sendAllExceptSender(msg, client);
						}
						else if (status == sf::Socket::Disconnected)
						{
							selector.remove(client);
							toRemove = &client;
							managerToRemove = &cm;
							std::cout << "\nclient has disconnected\n";
						}
					}
				}
				if (toRemove!=0) {
					clients.remove(toRemove);
					delete toRemove;
					cms.remove(managerToRemove);
					delete managerToRemove;
				}
			}
		}
	}
}

/**
* recieves MessageObject from the given client
* @param TcpSocket the client
* @return MessageObject
*/
MessageObject Server::recieve(sf::TcpSocket& client)
{
	sf::Packet packet;
	client.receive(packet);
	MessageObject m;
	packet >> m;
	return m;
}

/** TODO : remove this, we won't have commandline
* this method runs in its own thread
* gets input from commandline
*/
void Server::getInput()
{
	std::string in;
	while (isRunning)
	{
		getline(std::cin, in);
		if (in == "quit")
		{
			isRunning = false;
			shutDown();
		}
		else
		{
			MessageObject m(in);
			sendAll(m);
		}
	}
}

/**
* sends a message object to all of the clients, except to who sent it
* @param MessageObject the message
* @param TcpSocket the sender
*/
void Server::sendAllExceptSender(MessageObject m, sf::TcpSocket& sender)
{
	for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it!=clients.end(); ++it)
	{
		sf::TcpSocket& client = **it;
		if (client.getRemoteAddress() != sender.getRemoteAddress())
			send(m, client);
	}
}

/**
* sends a message object to all of the clients
* @param MessageObject
*/
void Server::sendAll(MessageObject m)
{
	for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it!=clients.end(); ++it)
	{
		sf::TcpSocket& client = **it;
		if (selector.isReady(client))
		{
			send(m, client);
		}
	}
}

/**
* sends a message object to the client
* @param MessageObject
* @param TcpSocket
*/
void Server::send(MessageObject m, sf::TcpSocket& client)
{
	sf::Packet packet;
	packet << m;
	client.send(packet);
}

/**
* sends a general message object to the client
* @param string
* @param TcpSocket
*/
void Server::send(std::string message, sf::TcpSocket& client)
{
	sf::Packet packet;
	MessageObject m(message);
	packet << m;
	client.send(packet);
}

/**
* sends a message object to the client
* @param int the message type
* @param string the message
* @param TcpSocket
*/
void Server::send(unsigned short i, std::string message, sf::TcpSocket& client)
{
	sf::Packet packet;
	MessageObject m(i, message);
	packet << m;
	client.send(packet);
}

/**
* shuts down the server<br>
* sends a shutdown command message to all the clients, and closes the connection
*/
void Server::shutDown()
{
	//for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it!=clients.end(); ++it)
	for (std::list<ClientManager*>::iterator it = cms.begin(); it!=cms.end(); ++it)
	{
		ClientManager& cm = **it;
		sf::TcpSocket& client = * cm.getSocket();
		if (selector.isReady(client))
		{
			send(MessageObject::MESSAGES::CMD, "shut", client);
			//send("shut", client);
		}
		else
		{
			std::cout << "socket not ready " << client.getRemoteAddress() << std::endl;
		}
		delete cm.getSocket();
		delete *it;
		//clients.erase(it);
	}
	listener.close();
}

/**
* destructor<br>
* if server was running, calls the shutdown method
*/
Server::~Server()
{
	if (isRunning)
		shutDown();
	std::cout << "server has been closed\n";
}