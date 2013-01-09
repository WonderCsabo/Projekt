#include "AbstractView.h"
#include <vector>

AbstractView::AbstractView(sf::RenderWindow *rw) : window(rw) {}
AbstractView::~AbstractView() {}
void AbstractView::addInputChat(const std::string &s)
{
    inputText = s;
}
void AbstractView::addOutputChat(const std::string &s)
{
    outputText.push_back(s);
    if (outputText.size()>24)
        outputText.pop_front();
}