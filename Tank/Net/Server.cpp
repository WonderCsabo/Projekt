#include "Server.h"

/**
* constructor
* server starts listening on the specified port
* also starts the thread for user input and starts waiting for clients
*/
Server::Server(unsigned int port_) : port(port_)
{
	std::cout << "Server started\nListening on port " << port << std::endl;
	std::cout << "public ip address: " << sf::IpAddress::getPublicAddress().toString() << std::endl
			  << "local ip address " << sf::IpAddress::getLocalAddress() << std::endl;
	listener.listen(port);
	selector.add(listener);
	isRunning = true;
	//messages = new std::map<std::string, std::deque<MessageObject>>();
	launch();
}

void Server::launch()
{
	sf::Thread input(&Server::getInput, this);
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
					std::cout << "mgr> ";
					MessageObject m = recieve(*client);
					std::cout << m.message << std::endl;
					send("I'm not the server You're looking for...", *client);
					ClientManager* cm = new ClientManager(client, m.message);
					cms.push_back(cm);
					cm->run();
					selector.add(*client);
				}
			}
			else
			{
				sf::TcpSocket* toRemove = 0;
				ClientManager* managerToRemove = 0;
				for (std::list<ClientManager*>::iterator it = cms.begin(); it!=cms.end(); ++it)
				{
					ClientManager* cm = *it;
					sf::TcpSocket* client = cm->getSocket();
					if (selector.isReady(*client))
					{
						MessageObject msg;
						sf::Packet packet;
						sf::TcpSocket::Status status = client->receive(packet);
						packet >> msg;
						
						if (status == sf::Socket::Done) {
							cm->appendMessage(msg);
							sendAllExceptSender(msg, *client);
						}
						else if (status == sf::Socket::Disconnected)
						{
							std::cout << "client has disconnected from " << client->getRemoteAddress() << std::endl;
							selector.remove(*client);
							toRemove = client;
							managerToRemove = cm;
						}
					}
				}
				if (toRemove!=0) {
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
	for (std::list<ClientManager*>::iterator it = cms.begin(); it!=cms.end(); ++it)
	{
		ClientManager* cm = *it;
		sf::TcpSocket* client = cm->getSocket();
		if (client->getRemoteAddress() != sender.getRemoteAddress())
			send(m, *client);
	}
}

/**
* sends a message object to all of the clients
* @param MessageObject
*/
void Server::sendAll(MessageObject m)
{
	std::list<ClientManager*>::iterator it = cms.begin();
	while(it!=cms.end())
	{
		ClientManager* cm = *it;
		sf::TcpSocket* socket = cm->getSocket();
		if (send(m, *socket) == sf::Socket::Done)
		{
			++it;
		}
		else
		{
			ClientManager* remove = cm;
			it = cms.erase(it);
			selector.remove(*socket);
			delete cm->getSocket();
			delete cm;
		}
	}
}
/*
void Server::recieveTank(sf::TcpSocket& client)
{
    sf::Packet packet;
    client.receive(packet);
    std::stringstream ss;
    ss.write((char*) packet.getData(), packet.getDataSize());
    Tank tank;
    ss >> tank;
    std::cout << tank.getPosX() << " " << tank.getPosY() << " " << tank.getSizeX() << " " << tank.getSizeY() << " " << tank.getTypeID() << std::endl;
}
*/
/**
* sends a message object to the client
* @param MessageObject
* @param TcpSocket
*/
sf::Socket::Status Server::send(MessageObject m, sf::TcpSocket& client)
{
	sf::Packet packet;
	packet << m;
	return client.send(packet);
}

/**
* sends a general message object to the client
* @param string
* @param TcpSocket
*/
sf::Socket::Status Server::send(std::string message, sf::TcpSocket& client)
{
	MessageObject m(message);
	return send(m, client);
}

/**
* sends a message object to the client
* @param int the message type
* @param string the message
* @param TcpSocket
*/
sf::Socket::Status Server::send(unsigned short i, std::string message, sf::TcpSocket& client)
{
	MessageObject m(i, message);
	return send(m, client);
}

/**
* shuts down the server<br>
* sends a shutdown command message to all the clients, and closes the connection
*/
void Server::shutDown()
{
	std::cout << cms.size() << std::endl;
	MessageObject m(MessageObject::CMD, "shut");
	if (cms.size()!=0) {
		for (std::list<ClientManager*>::iterator it = cms.begin(); it!=cms.end(); ++it)
			(*it)->shutDown();
		sendAll(m);
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

	//delete messages;

	std::cout << "server has been closed\n";
}