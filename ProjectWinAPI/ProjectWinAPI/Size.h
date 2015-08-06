#ifndef SIZE_H
#define SIZE_H

namespace Drawing
{

	typedef struct Size
	{
		int Width;
		int Height;
		Size(int width, int height) : Width(width), Height(height) {};
	};

}

#endif