#include <utility>
#include <vector>
#include "house.h"

Letter::Letter(pair<int,int> from, pair<int,int> to) : from(from), to(to), state(LetterState::NEW)
{
	
}

void Letter::changeState(LetterState ls)
{
	state = ls;
}

House::House()
{
	
}

House::~House()
{
	
}

vector<Letter*> & House::getLetters()
{
	return letters;
}

