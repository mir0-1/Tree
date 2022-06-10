#include "CAvlTree.h"
#include <stdio.h>

void CAvlTree::visitNode(STreeNode* psTreeWalker)
{
	printf("AVL Visited node %d\n", psTreeWalker->iNumber);
}

CAvlTree::CAvlTree() : CBinarySearchTree() {}
