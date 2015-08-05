#ifndef POINT_H
#define POINT_H

//TODO: maybe add to Drawing namespace ??
typedef struct Point
{
	int X;
	int Y;
	Point(int x, int y) : X(x), Y(y) {};
};

#endif