#include "treenode.h"

TDatValue* TreeNode::GetCopy() {
	TreeNode* tmp = new TreeNode(Key, pValue, NULL, NULL);
	return tmp;
}
void TreeNode::Print() {
	cout << "Key " << Key << " ";
	if (pValue!=nullptr) pValue->Print();
 }