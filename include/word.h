#ifndef WORD_H_
#define WORD_H_
#include <string>
#include "datvalue.h"

class TWord : public TDatValue {
private:
    std::string word;
public:
    TWord(std::string w) : word(w) {}
    virtual TDatValue *GetCopy() override; // создание копии
    std::string GetWord() {return word;}
    void SetWord(const std::string &w) {word = w;}
    bool operator==(const TWord &w) const {return w.word == word;}
};
typedef TWord *PTWord;

#endif  // WORD_H_
