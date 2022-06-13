#pragma once
#include "CBinarySearchTree.h"

class CAvlTree : public CBinarySearchTree
{
	private:
		int nodeHeight(STreeNode* psNode);
		void updateHeights();
	public:
		bool insert(int iNumber, void* pvExtAllocData);
		bool remove(int iNumber);

		CAvlTree();
		~CAvlTree();
};

