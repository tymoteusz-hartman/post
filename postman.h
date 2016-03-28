#include <utility>
#include <vector>
#include "house.h"

using std::pair;
using std::vector;

enum class Direction { UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT };

class Postman
{
private:
	pair<int,int> position;
	vector<Letter*> letters;
public:
	Postman(pair<int,int>);
	void move(Direction);
	pair<int,int> getPosition() { return position; }
	int getLettersNumber() { return letters.size(); }
	void addLetters(vector<Letter*>&);
	vector<Letter*> & getLetters() { return letters; }
	void dropLetters() { letters.clear(); }
};

