#include "Control.h"
#include "Application.h"

Control::Control()
{
	this->parent = NULL;
	this->hWnd = NULL;
	this->Text = "";
	this->Location = new Drawing::Point(CW_USEDEFAULT, CW_USEDEFAULT);
	this->Size = new Drawing::Size(0, 0);
	Controls = new ControlCollection(this);
	this->style = WS_VISIBLE | WS_CHILD;
	this->styleEx = 0;
}

Control::~Control()
{
	//TODO delete all controls
	delete this->Controls;
	delete this->hWnd;
	delete this->Size;
	delete this->Location;
	delete this->Text;
	delete this->className;
}

void Control::ResumeLayout(bool performLayout)
{
	this->CreateControl();
}

void Control::SuspendLayout()
{
}

void Control::WndProc(Message *m)
{
	if ((HWND)m->LParam == this->hWnd)
	{
		switch (m->Msg)
		{
		case WM_COMMAND:
			switch (m->WParam)
			{
			case BN_CLICKED:
				this->Click(this, new EventArgs());
				break;
			}
			break;
		}
	}
	else
	{
		std::list<Control*>::iterator i;
		for (i = this->Controls->begin(); i != this->Controls->end(); ++i)
		{
			(*i)->WndProc(m);
		}
	}
}

void Control::CreateControl()
{
	hWnd = CreateWindowEx(
		this->styleEx,
		this->className,
		this->Text,
		this->style,
		this->Location->X,
		this->Location->Y,
		this->Size->Width,
		this->Size->Height,
		parent != NULL ? parent->hWnd : NULL,
		NULL,
		Application::hInstance,
		NULL
		);

	if (hWnd == NULL)
	{
		return;
	}

	HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hNormalFont, 0);

	std::list<Control*>::iterator i;
	for (i = this->Controls->begin(); i != this->Controls->end(); ++i)
	{
		(*i)->ResumeLayout(false);
	}

	ShowWindow(hWnd, Application::nCmdShow);
	UpdateWindow(hWnd);
}