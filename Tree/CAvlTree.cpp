#include "CAvlTree.h"
#include <stdio.h>

CAvlTree::CAvlTree() : CBinarySearchTree() 
{
	poTnStack = new CTnStack;
}

CAvlTree::~CAvlTree()
{
	delete poTnStack;
}
