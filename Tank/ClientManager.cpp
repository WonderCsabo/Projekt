#include "ClientManager.h"

ClientManager::ClientManager(sf::TcpSocket* client_, std::string nick) : 
	client(client_), nickname(nick)
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