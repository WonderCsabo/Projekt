#include "Controller/Controller.h"


#if defined WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
#else
int main()
#endif
{
	std::srand((unsigned)std::time( 0 ));
	//DebugWindow::openDebugWindow();
	Controller controller(700, 700, "Tank Battle");
	controller.run();
	return 0;
}