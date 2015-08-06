#ifndef FORM_H
#define FORM_H

#include <windows.h>

#include "Size.h"
#include "Control.h"
#include "ControlCollection.h"

class Form : public Control
{
public:
	Drawing::Size *ClientSize;
public:
	Form();
	~Form();
public:
	void ResumeLayout(bool performLayout);
	void WndProc(Message *m);
private:
	bool RegisterClass();
public:
	EventHandler FormClosing;
	EventHandler FormClosed;
};

#endif