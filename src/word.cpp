#include "word.h"

TDatValue *TWord::GetCopy() {
    return new TWord(word);
}
