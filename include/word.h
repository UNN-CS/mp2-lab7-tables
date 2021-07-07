#pragma once

#include "defines.h"

#include "datvalue.h"

#include <string>
#include <iostream>

class TWord : public TDatValue {
  public:
    TWord(std::string w = "") {
        word = w;
    }
    virtual PTDatValue GetCopy() const {
        return new TWord(word);
    }
    std::string GetWord() const {
        return word;
    }
    void SetWord(const std::string &w) {
        word = w;
    }
    TWord& operator=(const TWord &w) {
        if (this != &w) {
            word = w.word;
        }
        return *this;
    }
    bool operator==(const TWord &w) {
        return word == w.word;
    }
  protected:
    virtual void Print(std::ostream &os) {
        os << word;
    }
  
    std::string word;
};
