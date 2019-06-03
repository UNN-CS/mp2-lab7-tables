
#include <string>
#include "datavalue.h"

class TWord : public TDatValue {
private:
    std::string word;
public:
    TWord(std::string w) : word(w) {}
    virtual TDatValue *GetCopy() override; // ñîçäàíèå êîïèè
    std::string GetWord() {return word;}
    void SetWord(const std::string &w) {word = w;}
    bool operator==(const TWord &w) const {return w.word == word;}
};
typedef TWord *PTWord;
