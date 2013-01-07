#include "ClientManager.h"

/**
* constructs a client manager which processes the messages from the actual client
* @param TcpSocket the client's socket
* @param string the nickname
*/
ClientManager::ClientManager(sf::TcpSocket* c, std::string nick)
{
	nickname = nick;
	client = c;
	isRunning = true;
}

/**
* delete operations
*/
ClientManager::~ClientManager()
{
	delete pthread;
}

/**
* @return TcpSocket the client
*/
sf::TcpSocket* ClientManager::getSocket()
{
	return client;
}

/**
* @return string the nickanme
*/
std::string ClientManager::getNickname()
{
	return nickname;
}

/**
* shutdown method for the client manager
*/
void ClientManager::shutDown()
{
	isRunning = false;
	std::cout << "cms " << nickname << "> shut\n";
}

/**
* launches the client manager's thread
*/
void ClientManager::run()
{
	pthread = new sf::Thread(&ClientManager::process, this);
	pthread->launch();
}

/**
* @return bool true, if the CM is running
*/
bool ClientManager::running()
{
	return isRunning;
}	

/**
* appends message to the CM's message queue
* @param MessageObject the last incoming message
*/
void ClientManager::appendMessage(const MessageObject& m)
{
	msgs.push_back(m);
}

/**
* @return MessageObject the last message in the queue
*/
MessageObject ClientManager::getMessage()
{
	if (!msgs.empty()) {
		MessageObject ret = msgs.front();
		msgs.pop_front();
		std::cout << "mgr " << nickname << "> " << ret << std::endl;
		if (ret.type == MessageObject::CMD && ret.message == "DISC")
			shutDown();
		return ret;
	}
	else
	{
		MessageObject m;
		return m;
	}
}

/**
* start processing messages, this runs in its own thread
*/
void ClientManager::process()
{
	while(isRunning)
	{
		sf::sleep(sf::milliseconds(10));
		getMessage();
	}
}