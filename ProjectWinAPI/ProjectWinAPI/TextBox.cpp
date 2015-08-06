#include "TextBox.h"

TextBox::TextBox()
{
	this->className = "Edit";
	this->styleEx = WS_EX_CLIENTEDGE;
	this->style = WS_VISIBLE | WS_CHILD | ES_MULTILINE |
		WS_VSCROLL | ES_LEFT | ES_AUTOVSCROLL;
}

TextBox::~TextBox()
{
}


