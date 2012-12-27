#include "ClientManager.h"

ClientManager::ClientManager(sf::TcpSocket* client_, std::string nick) :
	 nickname(nick), client(client_)
{

}

ClientManager::~ClientManager()
{
	//delete client; //az�rt nem kell, mert disconnectn�l a servern�l van delete, ide segfaultot kapn�k
}

sf::TcpSocket* ClientManager::getSocket()
{
	return client;
}
