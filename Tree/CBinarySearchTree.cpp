#include "CBinarySearchTree.h"
#include <cstring>
#include <stdio.h>


STreeNode* CBinarySearchTree::newNode(int iNumber, void* pvAllocExtraData)
{
	STreeNode* sNode = new STreeNode;

	sNode->iNumber = iNumber;
	sNode->pvExtAllocData = pvAllocExtraData;
	sNode->psLeft = nullptr;
	sNode->psRight = nullptr;

	return sNode;
}

bool CBinarySearchTree::delNode_noChildrenCase(STreeNode* psTreeWalker, STreeNode* psWalkerParent)
{
	if (!psTreeWalker || !psWalkerParent)
		return false;

	if (psWalkerParent->psLeft == psTreeWalker)
	{
		delete psTreeWalker;
		psWalkerParent->psLeft = nullptr;
		return true;
	}

	else if (psWalkerParent->psRight == psTreeWalker)
	{
		delete psTreeWalker;
		psWalkerParent->psRight = nullptr;
		return true;
	}

	return false;
}

bool CBinarySearchTree::delNode_oneChildCase(STreeNode* psTreeWalker)
{
	if (!psTreeWalker)
		return false;

	STreeNode* psWalkerChild;

	if (psTreeWalker->psLeft)
		psWalkerChild = psTreeWalker->psLeft;

	else if (psTreeWalker->psRight)
		psWalkerChild = psTreeWalker->psRight;
	else
		return false;

	psTreeWalker->iNumber = psWalkerChild->iNumber;
	psTreeWalker->pvExtAllocData = psWalkerChild->pvExtAllocData;

	delete psWalkerChild;
	if (psTreeWalker->psLeft)
		psTreeWalker->psLeft = nullptr;
	else
		psTreeWalker->psRight = nullptr;

	return true;
}

bool CBinarySearchTree::delNode_twoChildrenCase(STreeNode* psTreeWalker)
{
	STreeNode* psRightTreeWalker;
	STreeNode* psRtwParent;

	psRtwParent = psTreeWalker;
	psRightTreeWalker = psTreeWalker->psRight;

	while (psRightTreeWalker && psRightTreeWalker->psLeft)
	{
		psRtwParent = psRightTreeWalker;
		psRightTreeWalker = psRightTreeWalker->psLeft;
	}

	psTreeWalker->iNumber = psRightTreeWalker->iNumber;
	psTreeWalker->pvExtAllocData = psRightTreeWalker->pvExtAllocData;

	return delNode(psRightTreeWalker, psRtwParent);
}

bool CBinarySearchTree::delNode(STreeNode* psTreeWalker, STreeNode* psTwParent)
{
	if (psTreeWalker && psTwParent)
	{
		bool bTwHasLeftChild = (psTreeWalker->psLeft != nullptr);
		bool bTwHasRightChild = (psTreeWalker->psRight != nullptr);

		if (!bTwHasLeftChild && !bTwHasRightChild)
			return delNode_noChildrenCase(psTreeWalker, psTwParent);

		if (!bTwHasLeftChild || !bTwHasRightChild)
			return delNode_oneChildCase(psTreeWalker);

		return delNode_twoChildrenCase(psTreeWalker);
	}

	return false;
}

void CBinarySearchTree::inorderTraverse(STreeNode* psRoot)
{
	if (psRoot == nullptr)
		return;

	if (psRoot->psLeft)
		inorderTraverse(psRoot->psLeft);

	printf("%d\t", psRoot->iNumber);

	if (psRoot->psRight)
		inorderTraverse(psRoot->psRight);
}



bool CBinarySearchTree::insert(int iNumber, void* pvExtAllocExtraData)
{
	STreeNode* psTreeWalker = psRoot;

	while (true)
	{
		if (!psTreeWalker)
		{
			psRoot = newNode(iNumber, pvExtAllocExtraData);
			return true;
		}

		if (iNumber < psTreeWalker->iNumber)
		{
			if (psTreeWalker->psLeft)
				psTreeWalker = psTreeWalker->psLeft;
			else
			{
				psTreeWalker->psLeft = newNode(iNumber, pvExtAllocExtraData);
				return true;
			}
		}

		else if (iNumber > psTreeWalker->iNumber)
		{
			if (psTreeWalker->psRight)
				psTreeWalker = psTreeWalker->psRight;

			else
			{
				psTreeWalker->psRight = newNode(iNumber, pvExtAllocExtraData);
				return true;
			}
		}

		else
			return false;

	}

	return false;
}


STreeNode* CBinarySearchTree::find(int iNumber, bool bExactMatch, STreeNode** ppsTwParent)
{
	STreeNode* psTreeWalker = psRoot;

	if (ppsTwParent)
		*ppsTwParent = nullptr;

	while (psTreeWalker)
	{
		if (iNumber == psTreeWalker->iNumber)
			return psTreeWalker;

		if (psTreeWalker->psLeft && iNumber < psTreeWalker->iNumber)
		{
			if (ppsTwParent)
				*ppsTwParent = psTreeWalker;

			psTreeWalker = psTreeWalker->psLeft;
		}

		else if (psTreeWalker->psRight && iNumber > psTreeWalker->iNumber)
		{
			if (ppsTwParent)
				*ppsTwParent = psTreeWalker;

			psTreeWalker = psTreeWalker->psRight;
		}

		else
			break;
	}

	if (!bExactMatch)
		return psTreeWalker;

	return nullptr;
}

bool CBinarySearchTree::remove(int iNumber)
{
	STreeNode* psTwParent;
	STreeNode* psTreeWalker = find(iNumber, true, &psTwParent);

	return delNode(psTreeWalker, psTwParent);
}

void CBinarySearchTree::inorderPrint()
{
	inorderTraverse(psRoot);
}

CBinarySearchTree::CBinarySearchTree()
{
	psRoot = nullptr;
}
