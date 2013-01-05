#include "GetInput.h"
#include "../Util/DebugWindow.h"

void recieveFromClient(AbstractView* view, Client* client, bool& run)
{
	DebugWindow d;
	while (run)
	{
		sf::sleep(sf::milliseconds(10));
		MessageObject m = client->getLastMessage();
		if (m.type == MessageObject::CMD && m.message == "shut")
		{
			client->shutDown();
			run = false;
		}
		else
		{
			if (m.message != "null")
				std::cout << m << std::endl;
		}
	}
}

char getChar(sf::Event& ev)
{
	if (ev.type == ev.KeyPressed)
	{
		if (ev.key.code>=0 && ev.key.code<=25)
		{
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
		else return 0;
	}
	else return 0;
}

std::string wrt(Client* client, sf::RenderWindow* window, sf::Text& consoleText, std::string& console, sf::Event& event, bool& writeToConsole)
{
	std::string ret_str = "";
	if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0))
	{
		writeToConsole = !writeToConsole;
		if (writeToConsole) console="";
	}

	if (writeToConsole && event.type == sf::Event::KeyPressed)
	{
		char c = getChar(event);
		if (c!=0)
			console+=c;
		if (console[0] == '0' && console.length()>1)
			console = console.substr(1, console.length());
		if (event.key.code==sf::Keyboard::Back && console.length()>1)
			console = console.substr(0, console.length()-1);
		if (event.key.code==sf::Keyboard::Return)
		{
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
