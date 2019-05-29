#include <iostream>
#include "tscantable.h"
#include "tword.h"

using namespace std;

int main() {
    TScanTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    cout<<*((TWord*)t.FindRecord("1"));
    t.DelRecord("1");
    return 0;
}
