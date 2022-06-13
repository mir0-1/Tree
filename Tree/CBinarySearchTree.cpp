#include "CBinarySearchTree.h"
#include <cstring>
#include <stdio.h>
#include <limits>


STreeNode* CBinarySearchTree::newNode(int iNumber, void* pvAllocExtraData)
{
	STreeNode* sNode = new STreeNode;

	sNode->iNumber = iNumber;
	sNode->pvExtAllocData = pvAllocExtraData;
	sNode->psLeft = nullptr;
	sNode->psRight = nullptr;

	if (poTnStack)
		poTnStack->push(sNode);

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
	STreeNode* psInorderSuccessor;
	STreeNode* psParent;

	if (!psTreeWalker || !psTreeWalker->psRight)
		return false;

	psInorderSuccessor = walkPathFromTo(psTreeWalker->psRight, INT_MIN, false, &psParent, false);

	psTreeWalker->iNumber = psInorderSuccessor->iNumber;
	psTreeWalker->pvExtAllocData = psInorderSuccessor->pvExtAllocData;

	return delNode(psInorderSuccessor, psParent);
}

bool CBinarySearchTree::delNode(STreeNode* psTreeWalker, STreeNode* psTwParent)
{
	if (psTreeWalker)
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

bool CBinarySearchTree::insert(int iNumber, void* pvExtAllocData)
{
	if (poTnStack)
		poTnStack->clear();

	STreeNode* psCvnParent;
	STreeNode* psClosestValueNode = walkPathFromTo(psRoot, iNumber, false, &psCvnParent, false);

	if (psClosestValueNode == nullptr)
	{
		psRoot = newNode(iNumber, pvExtAllocData);
		return true;
	}

	if (psClosestValueNode->psLeft == nullptr && iNumber < psClosestValueNode->iNumber)
	{
		psClosestValueNode->psLeft = newNode(iNumber, pvExtAllocData);
		return true;
	}

	if (psClosestValueNode->psRight == nullptr && iNumber > psClosestValueNode->iNumber)
	{
		psClosestValueNode->psRight = newNode(iNumber, pvExtAllocData);
		return true;
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


STreeNode* CBinarySearchTree::walkPathFromTo(STreeNode* psStart, int iNumber, bool bExactMatch, STreeNode** ppsTwParent, bool bIsSearchOnly)
{
	STreeNode* psTreeWalker = psStart;

	if (ppsTwParent)
		*ppsTwParent = nullptr;

	while (psTreeWalker)
	{
		if (poTnStack && !bIsSearchOnly)
			poTnStack->push(psTreeWalker);

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
	if (poTnStack)
		poTnStack->clear();

	STreeNode* psTwParent;
	STreeNode* psTreeWalker = walkPathFromTo(psRoot, iNumber, true, &psTwParent, false);

	return delNode(psTreeWalker, psTwParent);
}


ENodeMatchType CBinarySearchTree::find(int iNumber, bool bExactMatch)
{
	STreeNode* psResult = walkPathFromTo(psRoot, iNumber, bExactMatch, nullptr, true);

	if (psResult->iNumber == iNumber)
		return ENodeMatchType::EXACT_MATCH;

	if (!bExactMatch && psResult)
		return ENodeMatchType::CLOSEST_MATCH;
	
	return ENodeMatchType::NO_MATCH;
}

void CBinarySearchTree::inorderPrint()
{
	inorderTraverse(psRoot);
}

CBinarySearchTree::CBinarySearchTree()
{
	psRoot = nullptr;
}
