#include "Controller/Controller.h"


#if defined WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
#else
int main()
#endif
{
	std::srand((unsigned)std::time( 0 ));
	Controller controller(700, 700, "Tank Battle",0);
	controller.run();
	return 0;
}