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

STreeNode* CBinarySearchTree::util_insert(int iNumber, void* pvExtAllocData)
{
	STreeNode* psClosestValueNode = walkPathTo(iNumber, false, nullptr, false);
	STreeNode** ppsTargetNode = nullptr;

	if (psClosestValueNode == nullptr)
		ppsTargetNode = &psRoot;

	else if (psClosestValueNode->psLeft == nullptr && iNumber < psClosestValueNode->iNumber)
		ppsTargetNode = &psClosestValueNode->psLeft;

	else if (psClosestValueNode->psRight == nullptr && iNumber > psClosestValueNode->iNumber)
		ppsTargetNode = &psClosestValueNode->psRight;

	if (ppsTargetNode)
	{
		*ppsTargetNode = newNode(iNumber, pvExtAllocData);
		if (bBackwalk)
			(*ppsTargetNode)->uMetadata.psPrev = psClosestValueNode;
		return *ppsTargetNode;
	}

	return nullptr;
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


STreeNode* CBinarySearchTree::walkPathTo(int iNumber, bool bExactMatch, STreeNode** ppsTwParent, bool bIsSearchOnly)
{
	STreeNode* psTreeWalker = psRoot;
	STreeNode* psTwParent = nullptr;

	while (psTreeWalker)
	{
		if (iNumber == psTreeWalker->iNumber)
			return psTreeWalker;

		if (bBackwalk && !bIsSearchOnly)
			psTreeWalker->uMetadata.psPrev = psTwParent;

		if (psTreeWalker->psLeft && iNumber < psTreeWalker->iNumber)
		{
			psTwParent = psTreeWalker;
			psTreeWalker = psTreeWalker->psLeft;
		}

		else if (psTreeWalker->psRight && iNumber > psTreeWalker->iNumber)
		{
			psTwParent = psTreeWalker;
			psTreeWalker = psTreeWalker->psRight;
		}

		else
			break;
	}

	if (!bExactMatch)
	{
		if (ppsTwParent)
			*ppsTwParent = psTwParent;
		return psTreeWalker;
	}

	return nullptr;
}

bool CBinarySearchTree::remove(int iNumber)
{
	if (poTnStack)
		poTnStack->clear();

	STreeNode* psTwParent;
	STreeNode* psTreeWalker = walkPathTo(iNumber, true, &psTwParent, false);

	return delNode(psTreeWalker, psTwParent);
}


ENodeMatchType CBinarySearchTree::find(int iNumber, bool bExactMatch)
{
	STreeNode* psResult = walkPathTo(iNumber, bExactMatch, nullptr, true);

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
