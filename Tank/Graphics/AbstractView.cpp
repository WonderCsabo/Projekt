#include "AbstractView.h"
#include <vector>
AbstractView::AbstractView(sf::RenderWindow *rw, bool deb) : window(rw), debugMode(deb){}
AbstractView::AbstractView(sf::RenderWindow *rw) : window(rw), debugMode(false){}
AbstractView::~AbstractView(void)
{
}

void AbstractView::addDebugInfo(std::string s)
{
	if(debugMode==false) return;
	for(int i = 0; i < debugMessages.size(); i++)
		if(debugMessages[i]==s) return;
	debugMessages.push_back(s);
}