#include "CAvlTree.h"

int CAvlTree::nodeHeight(CTreeNode* poNode)
{
	if (poNode == nullptr)
		return -1;

	return poNode->uiHeight;
}

unsigned int CAvlTree::max(int val1, int val2)
{
	if (val1 >= val2)
		return val1;

	return val2;
}

int CAvlTree::getBalance(CTreeNode* poNode)
{
	if (poNode == nullptr)
		return 0;
	return nodeHeight(poNode->nextRight()) - nodeHeight(poNode->nextLeft());
}

CTreeNode* CAvlTree::leftRotate(CTreeNode* poOldRoot)
{
	if (!poOldRoot || !poOldRoot->nextRight())
		return nullptr;

	CTreeNode* poNewRoot = poOldRoot->nextRight();
	poOldRoot->nextRight(poNewRoot->nextLeft());
	poNewRoot->nextLeft(poOldRoot);

	poOldRoot->uiHeight = max(nodeHeight(poOldRoot->nextLeft()), nodeHeight(poOldRoot->nextRight())) + 1;
	poNewRoot->uiHeight = max(nodeHeight(poNewRoot->nextLeft()), nodeHeight(poNewRoot->nextRight())) + 1;

	return poNewRoot;
}

CTreeNode* CAvlTree::rightRotate(CTreeNode* poOldRoot)
{
	if (!poOldRoot || !poOldRoot->nextLeft())
		return nullptr;

	CTreeNode* poNewRoot = poOldRoot->nextLeft();
	poOldRoot->nextLeft(poNewRoot->nextRight());
	poNewRoot->nextRight(poOldRoot);

	poOldRoot->uiHeight = max(nodeHeight(poOldRoot->nextLeft()), nodeHeight(poOldRoot->nextRight())) + 1;
	poNewRoot->uiHeight = max(nodeHeight(poNewRoot->nextLeft()), nodeHeight(poNewRoot->nextRight())) + 1;

	return poNewRoot;
}

CTreeNode* CAvlTree::postOperation(CTreeNode* poTreeWalker)
{
	int iBalanceFactor;

	poTreeWalker->uiHeight = max(nodeHeight(poTreeWalker->nextLeft()), nodeHeight(poTreeWalker->nextRight())) + 1;
	iBalanceFactor = getBalance(poTreeWalker);

	if (iBalanceFactor < -1)
	{
		int iLeftBalance = getBalance(poTreeWalker->nextLeft());

		if (iLeftBalance >= 1)
			poTreeWalker->nextLeft(leftRotate(poTreeWalker->nextLeft()));

		poTreeWalker = rightRotate(poTreeWalker);
	}

	else if (iBalanceFactor > 1)
	{
		int iRightBalance = getBalance(poTreeWalker->nextRight());

		if (iRightBalance <= -1)
			poTreeWalker->nextRight(rightRotate(poTreeWalker->nextRight()));

		poTreeWalker = leftRotate(poTreeWalker);
	}

	return poTreeWalker;
}