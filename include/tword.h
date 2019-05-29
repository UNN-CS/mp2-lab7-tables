#ifndef __T_WORD_H__
#define __T_WORD_H__

#include <iostream>
#include <string>
#include "tdatvalue.h"

class TWord: public TDatValue {
protected:
    std::string Word;
public:
    TWord(std::string w = "") {Word = w;}
    virtual TDatValue* GetCopy();
    std::string GetWord() {return Word;}
    void SetWord(std::string& w) {Word = w;}
    TWord& operator=(const TWord& w) {Word = w.Word; return* this;}
    bool operator==(const TWord& w) {return Word == w.Word;}
    friend std::ostream& operator<<(std::ostream& out, const TWord& w) {
        std::cout<<w.Word;
        return out;
    }
};

#endif // __T_WORD_H__
