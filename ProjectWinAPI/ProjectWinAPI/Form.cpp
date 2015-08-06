#include "Form.h"
#include "Application.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

Form::Form()
{
	this->style = WS_OVERLAPPEDWINDOW;
	this->styleEx = WS_EX_CLIENTEDGE;
}

Form::~Form()
{
}

bool Form::RegisterClass()
{
	this->className = this->Name;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Application::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Application::hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = this->className;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wcex) != 0;
}

void Form::ResumeLayout(bool performLayout)
{
	if (!RegisterClass())
	{
		return;
	}

	if (this->ClientSize != NULL)
	{
		this->Size = new Drawing::Size(this->ClientSize->Width + 16, this->ClientSize->Height + 39);
	}

	this->CreateControl();
}

void Form::WndProc(Message *m)
{
	switch (m->Msg)
	{
	case WM_CLOSE: {
		FormClosing(this, new EventArgs());
		DestroyWindow(this->hWnd);
	} break;
	case WM_DESTROY: {
		FormClosed(this, new EventArgs());
		PostQuitMessage(0);
	} break;
	default:
		Control::WndProc(m);
	}
}