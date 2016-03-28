#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include "engine.h"

using std::cout;
using std::cin;
using std::find;
using std::vector;
using std::set;
using std::string;
using std::stringstream;

Engine::Engine()
{
	map = new Map(pair<int,int>(4, 5));
	map->generate();
}

Engine::~Engine()
{
	for(auto letter : letters)
		delete letter;
	for(auto postman : postmen)
		delete postman;
	delete map;
}

void Engine::start()
{
	bool run = true;
	while(run)
	{
		if(rand() % 2)
		{
			int p, q;
			do
			{
				p = rand() % map->getDims().first;
				q = rand() % map->getDims().second;
			} while(map->fields[p][q].type != FieldType::HOUSE);	
			int r, s;
			do
			{
				r = rand() % map->getDims().first;
				s = rand() % map->getDims().second;
			} while(map->fields[r][s].type != FieldType::HOUSE);
			Letter * letter = new Letter(pair<int,int>(p,q), pair<int,int>(r,s));
			map->fields[p][q].house->getLetters().push_back(letter);
			letters.push_back(letter);
		}

		// draw
		cout << string(100, '\n');
		printMap();
		cout << "Post : " << map->getPost().first << "," << map->getPost().second << "\n";
		printLetters();
		printPostmen();

		// handle user input
		string input;
		bool retry;
		do {
			retry = false;
			cout << "cmd>";
			getline(cin, input);
			vector<string> words;
			const char delim = ' ';
			stringstream stream(input);
			string word;
			while(getline(stream, word, delim))
				words.push_back(word);
			if(words[0] == "a")
				// add postman: a
				postmen.push_back(new Postman(map->getPost()));
			else if(words[0] == "m")
			{
				// move: m <postmanId> <direction>
				int postmanId = stoi(words[1]);
				if(words[2] == "u")
					postmen[postmanId]->move(Direction::UP);
				else if(words[2] == "ur")
					postmen[postmanId]->move(Direction::UP_RIGHT);
				else if(words[2] == "r")
					postmen[postmanId]->move(Direction::RIGHT);
				else if(words[2] == "dr")
					postmen[postmanId]->move(Direction::DOWN_RIGHT);
				else if(words[2] == "d")
					postmen[postmanId]->move(Direction::DOWN);
				else if(words[2] == "dl")
					postmen[postmanId]->move(Direction::DOWN_LEFT);
				else if(words[2] == "l")
					postmen[postmanId]->move(Direction::LEFT);
				else if(words[2] == "ul")
					postmen[postmanId]->move(Direction::UP_LEFT);
			
			}
			else if(words[0] == "g")
			{
				// get letter: g <postmanId>
				int postmanId = stoi(words[1]);
				pair<int,int> postmanPosition = postmen[postmanId]->getPosition();
				if(map->fields[postmanPosition.first][postmanPosition.second].type == FieldType::HOUSE)
				{				
					vector<Letter*> lettersToAdd = map->fields[postmanPosition.first][postmanPosition.second].house->getLetters();
					for(auto letter : lettersToAdd)
						letter->changeState(LetterState::TO_POST);
					postmen[postmanId]->addLetters(lettersToAdd);
					map->fields[postmanPosition.first][postmanPosition.second].house->clearLetters();
				} else if(map->fields[postmanPosition.first][postmanPosition.second].type == FieldType::POST)
				{
					printLetters(&postLetters);
					
					// handle additional user input
					string addInput;
					getline(cin, addInput);
					set<int> params;
					stringstream addStream(addInput);
					string param;
					while(getline(addStream, param, delim))
						params.insert(stoi(param));
					
					vector<Letter*> exchangeLetters;				
					for(int i = 0; i < postLetters.size(); i++)
						if(postLetters[i]->getState() == LetterState::STAMPED && params.find(i) != params.end())
							exchangeLetters.push_back(postLetters[i]);
					for(auto letter : exchangeLetters)
					{
						letter->changeState(LetterState::TO_RECEIVER);
						postLetters.erase(find(postLetters.begin(), postLetters.end(), letter));
					}
					postmen[postmanId]->addLetters(exchangeLetters);
					
					//postmen[postmanId]->addLetters(postLetters);
					//postLetters.clear();
				}
			}
			else if(words[0] == "d")
			{
				// drop letter: d <postmanId>
				int postmanId = stoi(words[1]);
				pair<int,int> postmanPosition = postmen[postmanId]->getPosition();
				if(postmanPosition == map->getPost())
				{
					vector<Letter*> lettersToDrop = postmen[postmanId]->getLetters();
					for(auto letter : lettersToDrop)
						letter->changeState(LetterState::POST);
					postLetters.insert(postLetters.end(), lettersToDrop.begin(), lettersToDrop.end());
					postmen[postmanId]->dropLetters();
				}
				else if(map->fields[postmanPosition.first][postmanPosition.second].type == FieldType::HOUSE)
					for(vector<Letter*>::iterator letter = postmen[postmanId]->getLetters().begin(); letter != postmen[postmanId]->getLetters().end();)
						if((*letter)->getState() == LetterState::STAMPED && (*letter)->getTo() == postmanPosition)
						{
							(*letter)->changeState(LetterState::DELIVERED);
							postmen[postmanId]->getLetters().erase(letter);
						}
						else
							letter++;
			}
			else if(words[0] == "s")
				for(auto letter : postLetters)
					letter->changeState(LetterState::STAMPED);
			else if(words[0] == "h")
			{
				cout << "List of possible commands:\n";
				cout << "\ta\t\t\t\tadd postman\n";
				cout << "\tm <postmanId> <direction>\tmove postman\n";
				cout << "\tg <postmanId>\t\t\tget letters\n";
				cout << "\td <postmanId>\t\t\tdrop letters\n";
				cout << "\ts\t\t\t\tstamp letters in post\n";
				cout << "\th\t\t\t\tdisplay help\n";
				cout << "\tq\t\t\t\tquit\n";
				retry = true;
			}
			else if(words[0] == "q")
				// quit: q
				run = false;
			else
			{
				cout << "\tInput not recognised. Type 'h' for help.\n";
				retry = true;
			}
		} while (retry);
	}
}

void Engine::printLetters(vector<Letter*> * lettersPtr)
{
	if(lettersPtr == nullptr)
		lettersPtr = &(this->letters);
	vector<Letter*> & letters = *lettersPtr;
	cout << "Letters\n";
	for(auto letter : letters)
	{
		cout << letter->getFrom().first << "," << letter->getFrom().second << "\t" << letter->getTo().first << "," << letter->getTo().second << "\tstate: ";
		switch(letter->getState())
		{
		case LetterState::NEW:
			cout << "NEW\n";
			break;
		case LetterState::TO_POST:
			cout << "TO_POST\n";
			break;
		case LetterState::POST:
			cout << "POST\n";
			break;
		case LetterState::STAMPED:
			cout << "STAMPED\n";
			break;
		case LetterState::TO_RECEIVER:
			cout << "TO_RECEIVER\n";
			break;
		case LetterState::DELIVERED:
			cout << "DELIVERED\n";
			break;
		}
	}
}

void Engine::addPostman()
{
	postmen.push_back(new Postman(pair<int,int>(map->getPost())));
}

void Engine::printPostmen()
{
	cout << "Postmen\n";
	for(auto postman : postmen)
		cout << postman->getPosition().first << "," << postman->getPosition().second << " : " << postman->getLettersNumber() << "\n";
}

void Engine::printMap()
{
	pair<int,int> mapDims = map->getDims();
	for(int j = 0; j < mapDims.first; j++)
		cout << "  " << j;
	cout << "\n -";
	for(int j = 0; j < mapDims.first; j++)
		cout << "---";
	cout << "\n";
	for(int i = 0; i < mapDims.second; i++)
	{
		cout << i << "|";
		for(int j = 0; j < mapDims.first; j++)
		{
			FieldType fieldType = map->fields[j][i].type;
			cout << map->fields[j][i].getLetterFieldType();
			if(fieldType == FieldType::HOUSE)
				cout << map->fields[j][i].house->getLettersNumber();
			else if(fieldType == FieldType::POST)
				cout << postLetters.size();
			else
				cout << " ";
			cout << "|";
		}
		cout << "\n |";
		for(int j = 0; j < mapDims.first; j++)
			cout << " " << getPostmenNumber(pair<int,int>(j,i)) << "|";
		cout << "\n -";
		for(int j = 0; j < mapDims.first; j++)
			cout << "---";
		cout << "\n";
	}
}

int Engine::getPostmenNumber(pair<int,int> position)
{
	int counter = 0;
	for(auto postman : postmen)
		if(postman->getPosition() == position)
			counter++;
	return counter;
}

