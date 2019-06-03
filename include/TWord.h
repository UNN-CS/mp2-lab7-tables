#pragma once
#include <string>
#include "TDatValue.h"

class TWord : public TDatValue {
protected:
	std::string Word;
public:
	TWord(std::string w = "") { Word = w; }
	virtual TDatValue* GetCopy() { return new TWord(Word); }
	std::string GetWord() { return Word; }
	void SetWord(std::string& w) { Word = w; }
	TWord& operator=(const TWord& w) { Word = w.Word; return*this; }
	bool operator==(const TWord& w) { return Word == w.Word; }
	friend std::ostream& operator<<(std::ostream& out, const TWord& w) {
		std::cout << w.Word;
		return out;
	}
};