#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#define _WINSOCKAPI_

#include "Control.h"
#include "Application.h"

class ImageButton : public Control
{
public:
	ImageButton();
	~ImageButton();

public:
	int ButtonId;
	int BitmapId;
};

#endif