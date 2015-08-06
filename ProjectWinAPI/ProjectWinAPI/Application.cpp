#include "Application.h"

MSG Application::msg;
HINSTANCE Application::hInstance = NULL;
int Application::nCmdShow = 0;
Form *Application::MainWindow = NULL;

void Application::Run(Form *form)
{
	if (form->hWnd == NULL)
	{
		msg.wParam = -1;
		return;
	}

	MainWindow = form;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int Application::GetExitCode()
{
	return msg.wParam;
}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (MainWindow != NULL)
	{
		MainWindow->WndProc(&Message::Create(hWnd, Msg, wParam, lParam));
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}