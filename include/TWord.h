#ifndef __T_WORD_H__
#define __T_WORD_H__

#include <string>
#include "tdatvalue.h"

class TWord : public TDatValue {
private:
	std::string word;
public:
	TWord(std::string w = "") : word(w) {}
	virtual TDatValue *GetCopy() {return new TWord(word);}
	std::string GetWord() { return word; }
	void SetWord(const std::string &w) { word = w; }
	bool operator==(const TWord &w) const { return w.word == word; }
};
typedef TWord *PTWord;
#endif //__T_WORD_H__