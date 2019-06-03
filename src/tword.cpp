#include "tword.h"


TDatValue *TWord::GetCopy() {
    return new TWord(word);
}       /*================================================*/
