#include "CAvlTree.h"
#include <stdio.h>

bool CAvlTree::insert(int iNumber, void* pvExtAllocData)
{
	STreeNode* psResult = CBinarySearchTree::util_insert(iNumber, pvExtAllocData);

	if (psResult == nullptr)
		return false;

	updateHeights(psResult);

	return true;
}

bool CAvlTree::remove(int iNumber)
{
	return false;
}

int CAvlTree::nodeHeight(STreeNode* psNode)
{
	if (psNode == nullptr)
		return -1;

	return psNode->uMetadata.uiHeight;
}

void CAvlTree::updateHeights(STreeNode* psPathWalker)
{
	STreeNode* psNextNode;

	while (psPathWalker)
	{
		psNextNode = psPathWalker->uMetadata.psPrev;

		if (nodeHeight(psPathWalker->psLeft) >= nodeHeight(psPathWalker->psRight))
			psPathWalker->uMetadata.uiHeight = nodeHeight(psPathWalker->psLeft) + 1;
		else
			psPathWalker->uMetadata.uiHeight = nodeHeight(psPathWalker->psRight) + 1;

		psPathWalker = psNextNode;
	}
}

CAvlTree::CAvlTree() : CBinarySearchTree()
{
	bBackwalk = true;
}

CAvlTree::~CAvlTree()
{
}
