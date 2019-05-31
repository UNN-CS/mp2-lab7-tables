#ifndef TW
#define TW

#include <iostream>
#include <string>
#include "TDatvalue.h"
using namespace std;
class TWord :public TDatValue
{
protected:
	string Word;
public:
	TWord(string w = "") { Word = w; }
	virtual TDatValue *  GetCopy();
	string GetWord() { return Word; }
	void SetWord(string& w) { Word = w; }
	TWord& operator=(const TWord& w) { Word = w.Word; return *this; }
	int operator== (const TWord& w) const { return Word == w.Word; }
	virtual void Print() {
		cout << Word << " ";
	}
protected:
	virtual void Print(ostream & out) { out << Word; }
};
typedef TWord* PWord;
#endif TW