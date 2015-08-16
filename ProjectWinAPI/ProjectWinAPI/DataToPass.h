#ifndef DATATOPASS_H
#define DATATOPASS_H

#include "ImageButton.h"

class DataToPass
{
public:
	HWND hForm1;
	HWND hTextView;
	HWND * hResultButtons;
	ImageButton ** gameButtons;
};

#endif