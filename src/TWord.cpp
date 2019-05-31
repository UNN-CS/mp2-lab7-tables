#include "TWord.h"

PTDatValue TWord::GetCopy()
{
	PTDatValue tmp = new TWord(Word);
	return tmp;
}