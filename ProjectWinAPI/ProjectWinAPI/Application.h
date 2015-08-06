#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>
#include "Form.h"

class Application
{
private:
	static MSG msg;
	static Form *MainWindow;
public:
	static HINSTANCE hInstance;
	static int nCmdShow;
public:
	static void Run(Form *form);
	static int GetExitCode();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif