#pragma once

class TDatValue
{
public:
    virtual TDatValue *GetCopy() = 0;
};

typedef TDatValue *PTDatValue;
