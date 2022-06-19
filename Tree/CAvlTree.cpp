#include "CAvlTree.h"

int CAvlTree::nodeHeight(STreeNode* psNode)
{
	if (psNode == nullptr)
		return -1;

	return psNode->uiHeight;
}

unsigned int CAvlTree::max(int val1, int val2)
{
	if (val1 >= val2)
		return val1;

	return val2;
}

int CAvlTree::getBalance(STreeNode* psNode)
{
	if (psNode == nullptr)
		return 0;
	return nodeHeight(psNode->psRight) - nodeHeight(psNode->psLeft);
}

STreeNode* CAvlTree::leftRotate(STreeNode* psOldRoot)
{
	if (!psOldRoot || !psOldRoot->psRight)
		return nullptr;

	STreeNode* psNewRoot = psOldRoot->psRight;
	psOldRoot->psRight = psNewRoot->psLeft;
	psNewRoot->psLeft = psOldRoot;

	psOldRoot->uiHeight = max(nodeHeight(psOldRoot->psLeft), nodeHeight(psOldRoot->psRight)) + 1;
	psNewRoot->uiHeight = max(nodeHeight(psNewRoot->psLeft), nodeHeight(psNewRoot->psRight)) + 1;

	return psNewRoot;
}

STreeNode* CAvlTree::rightRotate(STreeNode* psOldRoot)
{
	if (!psOldRoot || !psOldRoot->psLeft)
		return nullptr;

	STreeNode* psNewRoot = psOldRoot->psLeft;
	psOldRoot->psLeft = psNewRoot->psRight;
	psNewRoot->psRight = psOldRoot;

	psOldRoot->uiHeight = max(nodeHeight(psOldRoot->psLeft), nodeHeight(psOldRoot->psRight)) + 1;
	psNewRoot->uiHeight = max(nodeHeight(psNewRoot->psLeft), nodeHeight(psNewRoot->psRight)) + 1;

	return psNewRoot;
}

STreeNode* CAvlTree::postOperation(STreeNode* psTreeWalker)
{
	int iBalanceFactor;

	psTreeWalker->uiHeight = max(nodeHeight(psTreeWalker->psLeft), nodeHeight(psTreeWalker->psRight)) + 1;
	iBalanceFactor = getBalance(psTreeWalker);

	if (iBalanceFactor < -1)
	{
		int iLeftBalance = getBalance(psTreeWalker->psLeft);

		if (iLeftBalance >= 1)
			psTreeWalker->psLeft = leftRotate(psTreeWalker->psLeft);

		psTreeWalker = rightRotate(psTreeWalker);
	}

	else if (iBalanceFactor > 1)
	{
		int iRightBalance = getBalance(psTreeWalker->psRight);

		if (iRightBalance <= -1)
			psTreeWalker->psRight = rightRotate(psTreeWalker->psRight);

		psTreeWalker = leftRotate(psTreeWalker);
	}

	return psTreeWalker;
}