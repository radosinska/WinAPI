#ifndef CONTROL_H
#define CONTROL_H

#define _WINSOCKAPI_

#include <windows.h>
#include "ControlCollection.h"
#include "Size.h"
#include "Point.h"
#include "Message.h"
#include "EventHandler.h"

class Control
{
protected:
	LPSTR className;
	DWORD style;
	DWORD styleEx;
public:
	HWND hWnd;
	LPSTR Name;
	LPSTR Text;
	Drawing::Point *Location;
	Drawing::Size *Size;
	bool UseVisualStyleBackColor;
	int TabIndex;
	bool TabStop;
	bool AutoSize;
	ControlCollection *Controls;
public:
	Control();
	~Control();
public:
	void ResumeLayout(bool performLayout);
	void SuspendLayout();
	void CreateControl();
public: //protected:
	virtual void WndProc(Message *m);
public:
	Control *parent;
public:
	EventHandler Click;
};

#endif