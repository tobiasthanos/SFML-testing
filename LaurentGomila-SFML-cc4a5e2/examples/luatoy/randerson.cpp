#include "randerson.h"


int Randerson::between(int low, int high)
{
	return low + generator.randInt(high-low);
}
/*
Point Randerson::between(int lowx, int highx, int lowy, int highy)
{
	Point temp;
	temp.x = lowx + generator.randInt(highx-lowx);
	temp.y = lowy + generator.randInt(highy-lowy);
	return temp;
}
*/
int Randerson::averagedrand(int min, int max, int averageness)
{
	int out = 0;
	for(int i = 0; i<averageness; i++)
	{
		out+=min+generator.randInt(max);
	}
	out = out/averageness;
	return out;
}
/*
Color Randerson::randcolor()
{
	Color temp;
	temp.red=between(0,255);
	temp.green=between(0,255);
	temp.blue=between(0,255);
	return temp;
}
*/
