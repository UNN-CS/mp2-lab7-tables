#include "balancenode.h"

TDatValue* BalanceNode::GetCopy() {
	BalanceNode* tmp = new BalanceNode(Key, pValue, NULL, NULL, BalOK);
	return tmp;
}