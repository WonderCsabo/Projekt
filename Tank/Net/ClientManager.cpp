#include "ClientManager.h"

ClientManager::ClientManager(sf::TcpSocket* client_, std::string nick) :
	 nickname(nick), client(client_)
{

}

ClientManager::~ClientManager()
{
	//delete client; //azért nem kell, mert disconnectnél a servernél van delete, ide segfaultot kapnék
}

sf::TcpSocket* ClientManager::getSocket()
{
	return client;
}
