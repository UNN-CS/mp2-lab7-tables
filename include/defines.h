#pragma once

#include <string>

constexpr int TabMaxSize = 25;

enum TDataPos    {FIRST_POS, CURRENT_POS, LAST_POS};
enum TSortMethod {INSERT_SORT, MERGE_SORT, QUIQ_SORT};

using TKey = std::string;

class TDatValue;   using PTDatValue   = TDatValue*;
class TTabRecord;  using PTTabRecord  = TTabRecord*;
class TTable;      using PTTable      = TTable*;
class TArrayTable; using PTArrayTable = TArrayTable*;
class TScanTable;  using PTScanTable  = TScanTable*;
class TSortTable;  using PTSortTable  = TSortTable*;
class TTreeNode;   using PTTreeNode   = TTreeNode*;
class TTreeTable;  using PTTreeTable  = TTreeTable*;

class TArrayHash;  using PTArrayHash  = TArrayHash*;
class TListHash;   using PTListHash   = TListHash*;
