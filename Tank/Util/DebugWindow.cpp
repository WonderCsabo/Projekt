#include "DebugWindow.h"
#include "Os.h"
 
DebugWindow::DebugWindow() {

#if defined WINDOWS
	AllocConsole();
	freopen("conin$","r",stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
#endif
}

DebugWindow::~DebugWindow() {
#if defined WINDOWS
	std::cout << "closing window";
	FreeConsole();
#endif

}

void DebugWindow::openDebugWindow() {

	static DebugWindow window;
}