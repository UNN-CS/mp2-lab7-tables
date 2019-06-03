#ifndef __WORD_H__
#define __WORD_H__

#include <string>

#include "tdatvalue.h"

class TWord: public TDatValue {
private:
    std::string Word;
public:
    TWord(std::string w = ""): Word(w) {}
    virtual TDatValue* GetCopy();
    std::string GetWord() { return Word; }
    void SetWord(const std::string& w) { Word = w; }
    bool operator==(const TWord& w) const { return Word == w.Word; }
};

typedef TWord* PTWord;

#endif
