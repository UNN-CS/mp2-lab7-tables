#include "TStudentRecord.h"

TStudRec::TStudRec()
{
	if (marks_number > 0)
	{
		marks = new int[marks_number];
		for (int i = 0;i < marks_number;i++)
			marks[i] = 0;
	}
}

TStudRec::~TStudRec()
{
	delete[] marks;
}

TStudRec::TStudRec(int* _marks) {
	SetMarks(_marks);
}

TStudRec::TStudRec(const TStudRec& tsr) {
	for (int i = 0;i < marks_number;i++)
		marks[i] = tsr.marks[i];
}

void TStudRec::SetMarks(int* _marks) {
	for (int i = 0;i < marks_number;i++)
		marks[i] = _marks[i];
}

int* TStudRec::GetMarks() {
	return marks;
}

TDatValue* TStudRec::GetCopy() {
	PTDatValue tmp = new TStudRec(marks);
	return tmp;
}