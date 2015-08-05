#include "Form.h"
#include "Application.h"

#include <list>

Form::Form()
{
	this->Controls = new ControlCollection(this);
}

Form::~Form()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

void Form::ResumeLayout(bool performLayout)
{
	hWnd = NULL;

	WNDCLASSEX wce;

	wce.cbSize = sizeof(WNDCLASSEX);
	wce.style = 0;
	wce.lpfnWndProc = WndProc;
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hInstance = Application::hInstance;
	wce.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wce.lpszMenuName = NULL;
	wce.lpszClassName = this->Name;
	wce.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wce))
	{
		return;
	}

	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		this->Name,
		this->Text,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		320,
		240,
		NULL,
		NULL,
		Application::hInstance,
		NULL
		);

	if (hWnd == NULL)
	{
		return;
	}

	///
	std::list<Control*>::iterator control;
	for (control = this->Controls->begin();
		control != this->Controls->end();
		++control)
	{
		(*control)->CreateControl();
	}

	ShowWindow(hWnd, Application::nCmdShow);
	UpdateWindow(hWnd);
}