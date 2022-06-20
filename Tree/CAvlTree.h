#pragma once
#include "CBinarySearchTree.h"

class CAvlTree : public CBinarySearchTree
{
	private:
		int nodeHeight(CTreeNode* poNode);
		unsigned int max(int val1, int val2);
		int getBalance(CTreeNode* poNode);
		CTreeNode* leftRotate(CTreeNode* poNode);
		CTreeNode* rightRotate(CTreeNode* poNode);

		CTreeNode* postOperation(CTreeNode* poTreeWalker);

};
