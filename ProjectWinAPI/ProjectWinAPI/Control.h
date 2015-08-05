#ifndef CONTROL_H
#define CONTROL_H

#include <windows.h>

#include "Size.h"
#include "Point.h"

class Control
{
public:
	HWND hWnd;
	LPSTR Name;
	LPSTR Text;
	Control *parent;
public:
	Drawing::Size *Size;
	Point *Location;
public:
	Control();
	~Control();
public:
	virtual void CreateControl();
};

#endif