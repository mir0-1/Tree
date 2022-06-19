#include "CBinarySearchTree.h"
#include <cstring>
#include <stdio.h>
#include <limits>


STreeNode* CBinarySearchTree::util_rm_caseOneChild(STreeNode* psToBeRmed, STreeNode* psCopyToNode)
{
	if (psToBeRmed == nullptr || (psToBeRmed->psLeft && psToBeRmed->psRight))
		return psToBeRmed;

	STreeNode* psChildTree = psToBeRmed->psLeft ? psToBeRmed->psLeft : psToBeRmed->psRight;

	if (psCopyToNode)
	{
		psCopyToNode->iNumber = psToBeRmed->iNumber;
		psCopyToNode->pvExtAllocData = psToBeRmed->pvExtAllocData;
	}

	delete psToBeRmed;
	psToBeRmed = psChildTree;

	return psToBeRmed;
}

STreeNode* CBinarySearchTree::util_rm_noChildren(STreeNode* psToBeRmed, STreeNode* psCopyToNode)
{
	if (psToBeRmed == nullptr)
		return nullptr;

	if (psCopyToNode)
	{
		psCopyToNode->iNumber = psToBeRmed->iNumber;
		psCopyToNode->pvExtAllocData = psToBeRmed->pvExtAllocData;
	}

	delete psToBeRmed;
	psToBeRmed = nullptr;

	return nullptr;
}

STreeNode* CBinarySearchTree::util_rm_twoChildren(STreeNode* psToBeRmed)
{
	if (psToBeRmed)
		psToBeRmed->psRight = util_remove(psToBeRmed->psRight, INT_MIN, psToBeRmed);
	return psToBeRmed;
}

STreeNode* CBinarySearchTree::postOperation(STreeNode* psTreeWalker)
{
	return psTreeWalker;
}

void CBinarySearchTree::onNodeTraverse(STreeNode *psNode, void* pvExtraArgs)
{
	printf("%d\t", psNode->iNumber);
}

STreeNode* CBinarySearchTree::util_rm_dispatchCases(STreeNode* psToBeRmed, STreeNode* psCopyToNode)
{
	if (psToBeRmed == nullptr)
		return nullptr;

	if ((bool)psToBeRmed->psLeft != (bool)psToBeRmed->psRight)
		psToBeRmed = util_rm_caseOneChild(psToBeRmed, psCopyToNode);

	else if (psToBeRmed->psLeft && psToBeRmed->psRight)
		psToBeRmed = util_rm_twoChildren(psToBeRmed);

	else if (!psToBeRmed->psLeft && !psToBeRmed->psRight)
		psToBeRmed = util_rm_noChildren(psToBeRmed, psCopyToNode);

	return psToBeRmed;
}

STreeNode* CBinarySearchTree::newNode(int iNumber, void* pvExtAllocData)
{
	STreeNode* psNode = new STreeNode;

	psNode->iNumber = iNumber;
	psNode->pvExtAllocData = pvExtAllocData;
	psNode->psLeft = nullptr;
	psNode->psRight = nullptr;
	psNode->uiHeight = 0;

	return psNode;
}

STreeNode* CBinarySearchTree::util_insert(STreeNode* psTreeWalker, int iNumber, void* pvAllocExtraData)
{
	if (psTreeWalker == nullptr)
	{
		psTreeWalker = newNode(iNumber, pvAllocExtraData);
		return psTreeWalker;
	}

	if (iNumber < psTreeWalker->iNumber)
		psTreeWalker->psLeft = util_insert(psTreeWalker->psLeft, iNumber, pvAllocExtraData);

	else if (iNumber > psTreeWalker->iNumber)
		psTreeWalker->psRight = util_insert(psTreeWalker->psRight, iNumber, pvAllocExtraData);

	psTreeWalker = postOperation(psTreeWalker);
	return psTreeWalker;
}

STreeNode* CBinarySearchTree::util_remove(STreeNode* psTreeWalker, int iNumber, STreeNode* psPrecedessor)
{
	if (psTreeWalker == nullptr)
		return nullptr;

	if (iNumber == psTreeWalker->iNumber || psPrecedessor && (psTreeWalker->psLeft == nullptr))
	{
		psTreeWalker = util_rm_dispatchCases(psTreeWalker, psPrecedessor);
		return psTreeWalker;
	}

	if (iNumber < psTreeWalker->iNumber)
		psTreeWalker->psLeft = util_remove(psTreeWalker->psLeft, iNumber, psPrecedessor);

	else if (iNumber > psTreeWalker->iNumber)
		psTreeWalker->psRight = util_remove(psTreeWalker->psRight, iNumber, psPrecedessor);

	psTreeWalker = postOperation(psTreeWalker);
	return psTreeWalker;
}

void CBinarySearchTree::util_inorderTraverse(STreeNode* psRoot, void *pvExtraArgs)
{
	if (psRoot)
	{
		if (psRoot->psLeft)
			util_inorderTraverse(psRoot->psLeft, pvExtraArgs);

		onNodeTraverse(psRoot, pvExtraArgs);

		if (psRoot->psRight)
			util_inorderTraverse(psRoot->psRight, pvExtraArgs);
	}
}

void CBinarySearchTree::insert(int iNumber, void* pvExtAllocData)
{
	psRoot = util_insert(psRoot, iNumber, pvExtAllocData);
}

void CBinarySearchTree::remove(int iNumber)
{
	psRoot = util_remove(psRoot, iNumber, nullptr);
}

void CBinarySearchTree::inorderPrint()
{
	util_inorderTraverse(psRoot, nullptr);
}

CBinarySearchTree::CBinarySearchTree()
{
	psRoot = nullptr;
}
