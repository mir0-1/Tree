#pragma once
#include "CBinarySearchTree.h"

class CAvlTree : public CBinarySearchTree
{
	private:
		int nodeHeight(STreeNode* psNode);
		unsigned int max(int val1, int val2);
		int getBalance(STreeNode* psNode);
		STreeNode* leftRotate(STreeNode* psNode);
		STreeNode* rightRotate(STreeNode* psNode);

		STreeNode* postOperation(STreeNode* psTreeWalker);

};
