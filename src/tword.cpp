#include "tword.h"

TDatValue* TWord::GetCopy() {
    TDatValue *tmp = new TWord(Word);
    return tmp;
}
