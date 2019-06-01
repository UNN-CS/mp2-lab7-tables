#ifndef __TWORD_H
#define __TWORD_H

#include "datvalue.h"

class TWord : public TDatValue
{
protected:
    std::string Word;
public:
    TWord(std::string w = "") : Word(w) {}
    virtual TDatValue* GetCopy()
    {
        TDatValue* tmp = new TWord(Word);
        return tmp;
    }
    std::string GetWord() { return Word; }
    void SetWord(std::string& w) { Word = w; }
    TWord& operator = (const TWord& w) 
    { 
        Word = w.Word; 
        return *this;
    }
    bool operator == (const TWord& w) { return Word == w.Word; }
};

#endif