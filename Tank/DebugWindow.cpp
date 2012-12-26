#include "DebugWindow.h"
#include <Windows.h>

DebugWindow::DebugWindow() {
	AllocConsole();
	freopen("conin$","r",stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
}

DebugWindow::~DebugWindow() {
	FreeConsole();
}