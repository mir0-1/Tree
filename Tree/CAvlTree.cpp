#include "CAvlTree.h"
#include <stdio.h>

bool CAvlTree::insert(int iNumber, void* pvExtAllocData)
{
	bool bResult = CBinarySearchTree::insert(iNumber, pvExtAllocData);

	if (!bResult)
		return false;

	updateHeights();

	return true;
}

bool CAvlTree::remove(int iNumber)
{
	bool bResult = CBinarySearchTree::remove(iNumber);

	if (!bResult)
		return false;

	updateHeights();

	return true;
}

int CAvlTree::nodeHeight(STreeNode* psNode)
{
	if (psNode == nullptr)
		return -1;

	return psNode->uiHeight;
}

void CAvlTree::updateHeights()
{
	STreeNode* psPassedNode;

	while (psPassedNode = poTnStack->pop(nullptr))
	{
		if (nodeHeight(psPassedNode->psLeft) >= nodeHeight(psPassedNode->psRight))
			psPassedNode->uiHeight = nodeHeight(psPassedNode->psLeft) + 1;
		else
			psPassedNode->uiHeight = nodeHeight(psPassedNode->psRight) + 1;
	}
}

CAvlTree::CAvlTree() : CBinarySearchTree()
{
	poTnStack = new CTnStack;
}

CAvlTree::~CAvlTree()
{
	delete poTnStack;
}
