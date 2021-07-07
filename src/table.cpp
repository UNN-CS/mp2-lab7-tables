#include "table.h"

TTable::TTable() {
    dataCount = 0;
    efficiency = 0;
}

TTable::~TTable() {}

int TTable::GetDataCount() const {
    return dataCount;
}

int TTable::GetEfficiency() const {
    return efficiency;
}

bool TTable::IsEmpty() const {
    return dataCount == 0;
}
