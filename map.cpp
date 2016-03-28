#include <utility>
#include <cstdlib>
#include <ctime>
#include "map.h"

using std::pair;

Field::Field() : type(FieldType::EMPTY), house(nullptr) {}

char Field::getLetterFieldType()
{
	switch(type)
	{
	case FieldType::EMPTY:
		return 'E';
	case FieldType::HOUSE:
		return 'H';
	case FieldType::ROAD:
		return 'R';
	case FieldType::POST:
		return 'P';
	
	}
}

Map::Map(pair<int,int> dims) : dims(dims), houseNumber(0), post(pair<int,int>(0,0))
{
	fields = new Field*[dims.first];
	for(int i = 0; i < dims.first; i++)
		fields[i] = new Field[dims.second];
}

Map::~Map()
{
	for(int i = 0; i < dims.first; i++)
		delete[] fields[i];
	delete[] fields;
}

void Map::generate()
{
	srand(time(NULL));
	post.first = rand() % dims.first, post.second = rand() % dims.second;
	fields[post.first][post.second].type = FieldType::POST;
	houseNumber = rand() % (dims.first * dims.second / 4) + (dims.first * dims.second / 2);
	for(int i = 0; i < houseNumber; i++)
	{
		int p = rand() % dims.first, q = rand() % dims.second;
		while(fields[p][q].type == FieldType::POST)
		{
			p = rand() % dims.first;
			q = rand() % dims.second;
		}
		fields[p][q].type = FieldType::HOUSE;
		fields[p][q].house = new House();
	}
}

pair<int,int> Map::getDims()
{
	return dims;
}

pair<int,int> Map::getPost()
{
	return post;
}

/*vector<Letter*> & Map::getLetters(pair<int,int> position)
{
	return fields[position.first][position.second].house->getLetters();
}*/

