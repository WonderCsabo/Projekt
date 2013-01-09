#include "Convert.h"

int strtoint(std::string s)
{
    std::stringstream ss;
    ss << s;
    int i;
    ss >> i;
    return i;
}