#include "TextView.h"

TextView::TextView()
{
	this->className = "Edit";
	this->styleEx = WS_EX_CLIENTEDGE;
	this->style = WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_LEFT |
		ES_READONLY | WS_VSCROLL | ES_AUTOVSCROLL;
}

TextView::~TextView()
{
}




