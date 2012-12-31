#include "ClientManager.h"

ClientManager::ClientManager(sf::TcpSocket* c, std::string nick)
{
	nickname = nick;
	client = c;
	isRunning = true;
}

ClientManager::~ClientManager()
{
	delete pthread;
}

sf::TcpSocket* ClientManager::getSocket()
{
	return client;
}

std::string ClientManager::getNickname()
{
	return nickname;
}

void ClientManager::shutDown()
{
	isRunning = false;
	std::cout << "cms shut\n";
}

void ClientManager::run()
{
	pthread = new sf::Thread(&ClientManager::process, this);
	pthread->launch();
}

bool ClientManager::running()
{
	return isRunning;
}	

void ClientManager::appendMessage(const MessageObject& m)
{
	msgs.push_back(m);
}

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

void ClientManager::process()
{
	while(isRunning)
	{
		sf::sleep(sf::milliseconds(10));
		getMessage();
	}
}