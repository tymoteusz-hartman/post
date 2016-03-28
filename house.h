#pragma once
#include <utility>
#include <vector>

using std::pair;
using std::vector;

enum class LetterState { NEW, TO_POST, POST, STAMPED, TO_RECEIVER, DELIVERED };

class Letter
{
private:
	pair<int,int> from;
	pair<int,int> to;
	LetterState state;
public:
	Letter(pair<int,int>, pair<int,int>);
	pair<int,int> getFrom() { return from; }
	pair<int,int> getTo() { return to; }
	LetterState getState() { return state; }
	void changeState(LetterState);
};

class House
{
private:
	vector<Letter*> letters;
public:
	House();
	~House();
	int getLettersNumber() { return letters.size(); }
	vector<Letter*> & getLetters();
	void clearLetters() { letters.clear(); }
};

