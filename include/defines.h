#pragma once

#include <string>

constexpr int TabMaxSize  = 25;
constexpr int TabHashStep = 5;

constexpr int BalOk    =  0;
constexpr int BalLeft  = -1;
constexpr int BalRight =  1;

enum TDataPos    {FIRST_POS, CURRENT_POS, LAST_POS};
enum TSortMethod {INSERT_SORT, MERGE_SORT, QUIQ_SORT};
enum TLinkPos    {CURRENT, FIRST, LAST};

using TKey = std::string;

class TDatValue;    using PTDatValue    = TDatValue*;
class TTabRecord;   using PTTabRecord   = TTabRecord*;
class TTable;       using PTTable       = TTable*;
class TArrayTable;  using PTArrayTable  = TArrayTable*;
class TScanTable;   using PTScanTable   = TScanTable*;
class TSortTable;   using PTSortTable   = TSortTable*;
class TTreeNode;    using PTTreeNode    = TTreeNode*;
class TTreeTable;   using PTTreeTable   = TTreeTable*;
class TBalanceNode; using PTBalanceNode = TBalanceNode*;
class TArrayHash;   using PTArrayHash   = TArrayHash*;
class TListHash;    using PTListHash    = TListHash*;
class TDatList;     using PTDatList     = TDatList*;
class TDatLink;     using PTDatLink     = TDatLink*;
class TRootLink;    using PTRootLink    = TRootLink*;
class TWord;        using PTWord        = TWord*;

