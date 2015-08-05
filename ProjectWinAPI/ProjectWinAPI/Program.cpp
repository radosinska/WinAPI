#include <windows.h>
#include "Program.h"

#include "Application.h"
#include "Form1.h"

void Program::Main()
{
	Application::Run(new Form1());
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	Application::hInstance = hInstance;
	Application::nCmdShow = nCmdShow;

	Program::Main();

	return Application::GetExitCode();
}