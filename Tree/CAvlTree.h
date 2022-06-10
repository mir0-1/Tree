#pragma once
#include "CBinarySearchTree.h"

class CAvlTree : public CBinarySearchTree
{
	private:
		void visitNode(STreeNode*);

	public:
		CAvlTree();
};

