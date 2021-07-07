#pragma once

#include "defines.h"

#include "tabrecord.h"

class TTreeNode : public TTabRecord {
  public:
    TTreeNode(TKey k = "", PTDatValue pVal = nullptr,
            PTTreeNode pL = nullptr, PTTreeNode pR = nullptr);

    virtual PTDatValue GetCopy() const override;

    PTTreeNode GetLeft() const;
    PTTreeNode GetRight() const;
  protected:
    PTTreeNode pLeft, pRight;

    friend class TTreeTable;
    friend class TBalanceTree;
};
