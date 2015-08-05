#ifndef FORM_H
#define FORM_H

#include <windows.h>

#include "Size.h"
#include "Control.h"
#include "ControlCollection.h"

class Form : public Control
{
public:
	Form();
	~Form();
public:
	Drawing::Size *ClientSize;
	ControlCollection *Controls;
public:
	void ResumeLayout(bool performLayout);
};

#endif