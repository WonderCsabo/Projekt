#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <list>
#include <iostream>
#include <map>
#include <deque>
#include "MessageObject.h"
#include "Client.h"
#include "ClientManager.h"

class Server
{
public:
	Server(unsigned int);
	~Server();
	MessageObject recieve(sf::TcpSocket&);

private:
	unsigned int port;
	sf::TcpListener listener;
	//sf::TcpSocket client;
	sf::SocketSelector selector;
	bool isRunning;

	void waitForClients();
	//std::list<sf::TcpSocket*> clients;
	//std::map<std::string, std::deque<MessageObject>>* messages;
	std::list<ClientManager*> cms;
	void getInput();
	void shutDown();
	void launch();
	sf::Socket::Status send(std::string, sf::TcpSocket&);
	sf::Socket::Status send(unsigned short, std::string, sf::TcpSocket&);
	sf::Socket::Status send(MessageObject m, sf::TcpSocket&);
	void sendAll(MessageObject);
	void sendAllExceptSender(MessageObject, sf::TcpSocket&);
	//void recieveTank(sf::TcpSocket&);
};

#endif //SERVER_H