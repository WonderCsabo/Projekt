#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <exception>
#include <functional>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Graphics/View.h"
#include "Net/Client.h"
#include "GUI/StartGui.hpp"
#include "Util/DebugWindow.h"

/*
void recieveFromClient(AbstractView* view, Client* client, bool& run)
{
 DebugWindow w;

 while (run) {
  MessageObject m = client->recieve();
  if (m.type == MessageObject::CMD && m.message == "shut"){
   client->shutDown();
   run = false;
  }
  else
   view -> addDebugInfo(m.toString());

  std::cout << "loop" << std::endl;
 }
}
*/

void recieveFromClient(AbstractView* view, Client* client, bool& run)
{

	while (run) {
		MessageObject m = client->recieve();
		if (m.type == MessageObject::CMD && m.message == "shut"){
			client->shutDown();
			run = false;
		}
		else
			view -> addDebugInfo(m.toString());
	}
}

char getChar(sf::Event& ev)
{
	if (ev.type == ev.KeyPressed) {
	if (ev.key.code>=0 && ev.key.code<=25) {
			if (ev.key.shift==false)
				return char(97+ev.key.code);
			else
				return char(65+ev.key.code);
		}
		else if (ev.key.code==sf::Keyboard::Space)
			return ' ';
		else if (ev.key.code>=26 && ev.key.code<=35)
		{
			return char(48+ev.key.code-26);
		}
		else if (ev.key.code>=75 && ev.key.code<=84)
		{
			return char(48+ev.key.code-75);
		}
		else if (ev.key.code == sf::Keyboard::Period)
			return '.';
		else return NULL;
	}
}

std::string wrt(Client* client, sf::RenderWindow* window, sf::Text& consoleText, std::string& console, sf::Event& event, bool& writeToConsole)
{
	std::string ret_str = "";
	if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0)){
		writeToConsole = !writeToConsole;
		if (writeToConsole) console="";
	}

	if (writeToConsole && event.type == sf::Event::KeyPressed)
	{
		char c = getChar(event);
		if (c!=NULL)
			console+=c;
		if (console[0] == '0' && console.length()>1)
			console = console.substr(1, console.length());
		if (event.key.code==sf::Keyboard::Back && console.length()>1)
			console = console.substr(0, console.length()-1);
		if (event.key.code==sf::Keyboard::Return) {
			if (client!=NULL) client->send(console);
			ret_str = console;
			console = "";
			writeToConsole = false;
		}
		consoleText.setString(console);
		window->draw(consoleText);
	}
	return ret_str;
}

Client* startgui()
{
	StartGui* gui = new StartGui();
	return gui->getClient();
}
void addRandomBarrels(AbstractView* v)
{
	
	for(int i = 0; i< 50 ;i++)
	{
	v->addBarrel(std::rand()%700, std::rand()%700, (std::rand()%20+90)/100, (std::rand()%20+90)/100);
	}
}
void __stdcall WinMain(int a, short d, char * c, char* b)
{
	/*Client* client = startgui();
	if (client==NULL)
		return;*/
	//Client* client = new Client(54322, "192.168.1.67", "client0");

	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(700,700), "Tank Battle!", sf::Style::Close);
	AbstractView* view = new View(window,true);//a második paramért a debugolás kiírásához van, alapértelmezetten hamis
    std::srand((unsigned)std::time(0)); 
	addRandomBarrels(view);
	bool run = true;

	//sf::Thread thread(std::bind(&recieveFromClient, view, client, run));
	//thread.launch();
	
	std::string console = "";
	sf::Text consoleText;
	consoleText.setCharacterSize(10);
	consoleText.setColor(sf::Color(255,255,255));
	sf::Vector2f pos(10, 10);
	consoleText.setPosition(pos);
	bool writeToConsole = false;
	
	while (window->isOpen())
	{
		try 
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				sf::sleep(sf::milliseconds(10));

				if (event.type == sf::Event::Closed)
				{
					run = false;
					//thread.terminate();
					//client->shutDown();
					window->close();
				}

				//client->sendEventMessage(event);
				//wrt(client, window, consoleText, console, event, writeToConsole);
				
			}
			//view->addDebugInfo("Debug info1");
			//view->addDebugInfo("Debug info2");
			view->drawEverything();
			window->draw(consoleText);
			window->display();
			sf::sleep(sf::milliseconds(10));
		}
		catch(std::exception e)
		{
			e.what();
		}
	}
	/*
	if (client!=NULL) {
		client->shutDown();
		delete client;
	}*/

    return ;
}