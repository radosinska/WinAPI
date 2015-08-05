#ifndef SIZE_H
#define SIZE_H

//TODO: add to new director or delete namespace
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