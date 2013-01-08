#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include "MessageObject.h"
#include "../Logic/Player.h"
#include "../Logic/Map.h"
#include "../Util/Convert.h"

class Client
{
public:
	Client(unsigned int, sf::IpAddress, std::string);
	~Client();

	bool getMapChanged();
	Map* getMap();
	Player* getPlayer();

	sf::TcpSocket* getSocket();
	bool isConnected();
	std::string getNickname();
	void shutDown();
	
	void sendChanged();

	void send(std::string);
	MessageObject getLastMessage();
	void sendEventMessage(sf::Event&);	

private:
	sf::TcpSocket server;
	sf::IpAddress address;
	unsigned int port;
	bool isRunning;
	sf::Socket::Status status;
	std::string nickname;
	sf::Thread* manager;
	std::deque<MessageObject> messages;
	std::deque<MessageObject> sysmsg;
	Player* temp;
	bool isMapChanged;
	Player* player;
	Map* map;
	
	void send(MessageObject);
	void send(unsigned short, std::string);
	MessageObject recieve();

	void initGameProtocol();
	void manageClient();
	void getInput();
	void launch();
};
