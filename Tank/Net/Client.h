#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MessageObject.hpp"

class Client
{
public:
	Client(unsigned int, sf::IpAddress, std::string);
	~Client();
	bool canRemove;

	//void launch();

	sf::TcpSocket* getSocket();
	void sendEventMessage(sf::Event&);
	
	void shutDown();
	void send(std::string);
	MessageObject recieve();

private:
	sf::TcpSocket server;
	sf::IpAddress address;
	unsigned short port;
	bool isRunning;
	//sf::Thread input;

	void send(MessageObject);
	void send(unsigned short, std::string);

	void manageClient();
	void getInput();
};

#endif //CLIENT_H