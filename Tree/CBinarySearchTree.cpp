#include "CBinarySearchTree.h"
#include <cstring>
#include <stdio.h>


STreeNode* CBinarySearchTree::newNode(int iNumber, void* pvAllocExtraData, bool bUseStack)
{
	STreeNode* sNode = new STreeNode;

	sNode->iNumber = iNumber;
	sNode->pvExtAllocData = pvAllocExtraData;
	sNode->psLeft = nullptr;
	sNode->psRight = nullptr;

	if (bUseStack)
		oTnStack.push(sNode);

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

bool CBinarySearchTree::util_insert(int iNumber, void* pvExtAllocData, bool bUseStack)
{
	STreeNode* psCvnParent;
	STreeNode* psClosestValueNode = walkPathTo(iNumber, false, &psCvnParent, bUseStack);

	if (psClosestValueNode == nullptr)
	{
		psRoot = newNode(iNumber, pvExtAllocData, bUseStack);
		return true;
	}

	if (psClosestValueNode->psLeft == nullptr && iNumber < psClosestValueNode->iNumber)
	{
		psClosestValueNode->psLeft = newNode(iNumber, pvExtAllocData, bUseStack);
		return true;
	}

	if (psClosestValueNode->psRight == nullptr && iNumber > psClosestValueNode->iNumber)
	{
		psClosestValueNode->psRight = newNode(iNumber, pvExtAllocData, bUseStack);
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


STreeNode* CBinarySearchTree::walkPathTo(int iNumber, bool bExactMatch, STreeNode** ppsTwParent, bool bUseStack)
{
	STreeNode* psTreeWalker = psRoot;

	if (ppsTwParent)
		*ppsTwParent = nullptr;

	while (psTreeWalker)
	{
		if (bUseStack)
			oTnStack.push(psTreeWalker);

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

bool CBinarySearchTree::util_remove(int iNumber, bool bUseStack)
{
	STreeNode* psTwParent;
	STreeNode* psTreeWalker = walkPathTo(iNumber, true, &psTwParent, bUseStack);

	return delNode(psTreeWalker, psTwParent);
}


ENodeMatchType CBinarySearchTree::find(int iNumber, bool bExactMatch)
{
	STreeNode* psResult = walkPathTo(iNumber, bExactMatch, nullptr, false);

	if (psResult->iNumber == iNumber)
		return ENodeMatchType::EXACT_MATCH;

	if (!bExactMatch && psResult)
		return ENodeMatchType::CLOSEST_MATCH;
	
	return ENodeMatchType::NO_MATCH;
}

bool CBinarySearchTree::insert(int iNumber, void* pvExtAllocData)
{
	return util_insert(iNumber, pvExtAllocData, false);
}

bool CBinarySearchTree::remove(int iNumber)
{
	return util_remove(iNumber, false);
}

void CBinarySearchTree::inorderPrint()
{
	inorderTraverse(psRoot);
}

CBinarySearchTree::CBinarySearchTree()
{
	psRoot = nullptr;
}
