#include "postman.h"

Postman::Postman(pair<int,int> p) : position(p)
{

}

void Postman::move(Direction dir)
{
	switch(dir)
	{
	case Direction::UP:
		position.second -= 1;
		break;
	case Direction::UP_RIGHT:
		position.first += 1;
		position.second -= 1;
		break;
	case Direction::RIGHT:
		position.first += 1;
		break;
	case Direction::DOWN_RIGHT:
		position.first += 1;
		position.second += 1;
		break;
	case Direction::DOWN:
		position.second += 1;
		break;
	case Direction::DOWN_LEFT:
		position.first -= 1;
		position.second += 1;
		break;
	case Direction::LEFT:
		position.first -= 1;
		break;
	case Direction::UP_LEFT:
		position.first -= 1;
		position.second -= 1;
		break;
	}
}

void Postman::addLetters(vector<Letter*> & letters)
{
	this->letters.insert(this->letters.end(), letters.begin(), letters.end());
}

