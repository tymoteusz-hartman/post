#include "engine.h"

int main()
{
	Engine * e = new Engine();
	e->start();
	delete e;

	return 0;
}

