#pragma once
#include "CBinarySearchTree.h"

class CAvlTree : public CBinarySearchTree
{
	private:
		int nodeHeight(STreeNode* psNode);
		void updateHeightsAndRotate(int iInsertedNum);
		unsigned int max(int val1, int val2);
		int getBalance(STreeNode* psNode);
		STreeNode* leftRotate(STreeNode* psNode);
		STreeNode* rightRotate(STreeNode* psNode);
	public:
		bool insert(int iNumber, void* pvExtAllocData);
		bool remove(int iNumber);

		STreeNode* t_leftRotate();
		STreeNode* t_rightRotate();

		CAvlTree();
		~CAvlTree();
};

