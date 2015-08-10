#include "TextView.h"

TextView::TextView()
{
	this->className = "Static";
	this->styleEx = WS_EX_CLIENTEDGE;
	this->style = WS_VISIBLE | WS_CHILD | WS_VSCROLL;
}

TextView::~TextView()
{
}


