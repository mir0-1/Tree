#include "CAvlTree.h"

bool CAvlTree::insert(int iNumber, void* pvExtAllocData)
{
	bool bResult = CBinarySearchTree::insert(iNumber, pvExtAllocData);

	if (!bResult)
		return false;

	updateHeightsAndRotate(iNumber);

	return true;
}

bool CAvlTree::remove(int iNumber)
{
	bool bResult = CBinarySearchTree::remove(iNumber);

	if (!bResult)
		return false;

	updateHeightsAndRotate(iNumber);

	return true;
}

STreeNode* CAvlTree::t_leftRotate()
{
	return psRoot = leftRotate(psRoot);
}

STreeNode* CAvlTree::t_rightRotate()
{
	return psRoot = rightRotate(psRoot);
}

int CAvlTree::nodeHeight(STreeNode* psNode)
{
	if (psNode == nullptr)
		return -1;

	return psNode->uiHeight;
}

void CAvlTree::updateHeightsAndRotate(int iInsertedNum)
{
	STreeNode** ppsPassedNode;
	STreeNode* psPassedNode;
	int iBalanceFactor;

	while (ppsPassedNode = poTnStack->pop(nullptr))
	{
		psPassedNode = *ppsPassedNode;

		psPassedNode->uiHeight = max(nodeHeight(psPassedNode->psLeft), nodeHeight(psPassedNode->psRight)) + 1;
		iBalanceFactor = getBalance(psPassedNode);

		if (iBalanceFactor < -1)
		{
			int iLeftBalance = getBalance(psPassedNode->psLeft);

			if (iLeftBalance >= 1)
			{
				psPassedNode->psLeft = leftRotate(psPassedNode->psLeft);
				*ppsPassedNode = rightRotate(psPassedNode);
			}

			else
				*ppsPassedNode = rightRotate(psPassedNode);

		}

		else if (iBalanceFactor > 1)
		{
			int iRightBalance = getBalance(psPassedNode->psRight);

			if (iRightBalance <= -1)
			{
				psPassedNode->psRight = rightRotate(psPassedNode->psRight);
				*ppsPassedNode = leftRotate(psPassedNode);
			}

			else
				*ppsPassedNode = leftRotate(psPassedNode);
		}
	}

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


CAvlTree::CAvlTree() : CBinarySearchTree()
{
	poTnStack = new CTnStack;
}

CAvlTree::~CAvlTree()
{
	delete poTnStack;
}
