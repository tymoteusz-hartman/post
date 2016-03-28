#include <utility>
#include <vector>
#include "house.h"

using std::pair;
using std::vector;

enum class FieldType { EMPTY, HOUSE, ROAD, POST };

struct Field
{
	FieldType type;
	House * house;
	Field();
	char getLetterFieldType();
};

class Map
{
private:
	pair<int,int> dims;
	Field ** fields;
	int houseNumber;
	pair<int,int> post;
public:
	Map(pair<int,int>);
	~Map();
	void generate();
	pair<int,int> getDims();
	pair<int,int> getPost();
	// vector<Letter*> & getLetters(pair<int,int>);
	
	friend class Engine;
};

