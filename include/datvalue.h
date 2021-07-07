#pragma once

#include "defines.h"

class TDatValue {
  public:
    virtual PTDatValue GetCopy() const = 0;
};
