#ifndef RANDERSON_H
#define RANDERSON_H


struct Randerson
{
	MTRand generator;
	
	int between(int low, int high);
	//Point between(int lowx, int highx, int lowy, int highy);

	int averagedrand(int min, int max, int averageness);

	//Color randcolor();

};

#endif
