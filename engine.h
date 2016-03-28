#include <vector>
#include "map.h"
#include "postman.h"

using std::vector;

class Engine
{
private:
	Map * map;
	vector<Letter*> letters;
	void printLetters(vector<Letter*>* = nullptr);
	vector<Letter*> postLetters;
	vector<Postman*> postmen;
	void printPostmen();
	void printMap();
	int getPostmenNumber(pair<int,int>);
public:
	Engine();
	~Engine();
	void start();
	void addPostman();
};

