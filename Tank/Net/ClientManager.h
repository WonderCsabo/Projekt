#pragma once
#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Client.h"
#include <map>
#include <deque>

class ClientManager
{
public:
	ClientManager(sf::TcpSocket*, std::string);
	~ClientManager();

	sf::TcpSocket* getSocket();
	std::string getNickname();
	bool running();
	void shutDown();
	void run();

	void appendMessage(const MessageObject&);
	MessageObject getMessage();

private:
	std::string nickname;
	sf::TcpSocket* client;
	bool isRunning;
	std::deque<MessageObject> msgs;
	sf::Thread* pthread;

	void process();
};

#endif //CLIENTMANAGER_H