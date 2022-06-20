#include "CBinarySearchTree.h"
#include <cstring>
#include <stdio.h>
#include <limits>


CTreeNode* CBinarySearchTree::util_rm_caseOneChild(CTreeNode* psToBeRmed, CTreeNode* psCopyToNode)
{
	if (psToBeRmed == nullptr || (psToBeRmed->nextLeft() && psToBeRmed->nextRight()))
		return psToBeRmed;

	CTreeNode* psChildTree = psToBeRmed->nextLeft() ? psToBeRmed->nextLeft() : psToBeRmed->nextRight();

	if (psCopyToNode)
	{
		psCopyToNode->iNumber = psToBeRmed->iNumber;
		psCopyToNode->pvExtAllocData = psToBeRmed->pvExtAllocData;
	}

	delete psToBeRmed;
	psToBeRmed = psChildTree;

	return psToBeRmed;
}

CTreeNode* CBinarySearchTree::util_rm_noChildren(CTreeNode* psToBeRmed, CTreeNode* psCopyToNode)
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

CTreeNode* CBinarySearchTree::util_rm_twoChildren(CTreeNode* psToBeRmed)
{
	if (psToBeRmed)
		psToBeRmed->nextRight(util_remove(psToBeRmed->nextRight(), INT_MIN, psToBeRmed));
	return psToBeRmed;
}

CTreeNode* CBinarySearchTree::postOperation(CTreeNode* psTreeWalker)
{
	return psTreeWalker;
}

void CBinarySearchTree::onNodeTraverse(CTreeNode *psNode, void* pvExtraArgs)
{
	printf("%d\t", psNode->iNumber);
}

CTreeNode* CBinarySearchTree::util_rm_dispatchCases(CTreeNode* psToBeRmed, CTreeNode* psCopyToNode)
{
	if (psToBeRmed == nullptr)
		return nullptr;

	if ((bool)psToBeRmed->nextLeft() != (bool)psToBeRmed->nextRight())
		psToBeRmed = util_rm_caseOneChild(psToBeRmed, psCopyToNode);

	else if (psToBeRmed->nextLeft() && psToBeRmed->nextRight())
		psToBeRmed = util_rm_twoChildren(psToBeRmed);

	else if (!psToBeRmed->nextLeft() && !psToBeRmed->nextRight())
		psToBeRmed = util_rm_noChildren(psToBeRmed, psCopyToNode);

	return psToBeRmed;
}

CTreeNode* CBinarySearchTree::util_insert(CTreeNode* psTreeWalker, int iNumber, void* pvAllocExtraData)
{
	if (psTreeWalker == nullptr)
	{
		psTreeWalker = new CTreeNode(iNumber, pvAllocExtraData);
		return psTreeWalker;
	}

	if (iNumber < psTreeWalker->iNumber)
		psTreeWalker->nextLeft(util_insert(psTreeWalker->nextLeft(), iNumber, pvAllocExtraData));

	else if (iNumber > psTreeWalker->iNumber)
		psTreeWalker->nextRight(util_insert(psTreeWalker->nextRight(), iNumber, pvAllocExtraData));

	psTreeWalker = postOperation(psTreeWalker);
	return psTreeWalker;
}

CTreeNode* CBinarySearchTree::util_remove(CTreeNode* psTreeWalker, int iNumber, CTreeNode* psPrecedessor)
{
	if (psTreeWalker == nullptr)
		return nullptr;

	if (iNumber == psTreeWalker->iNumber || psPrecedessor && (psTreeWalker->nextLeft() == nullptr))
	{
		psTreeWalker = util_rm_dispatchCases(psTreeWalker, psPrecedessor);
		return psTreeWalker;
	}

	if (iNumber < psTreeWalker->iNumber)
		psTreeWalker->nextLeft(util_remove(psTreeWalker->nextLeft(), iNumber, psPrecedessor));

	else if (iNumber > psTreeWalker->iNumber)
		psTreeWalker->nextRight(util_remove(psTreeWalker->nextRight(), iNumber, psPrecedessor));

	psTreeWalker = postOperation(psTreeWalker);
	return psTreeWalker;
}

void CBinarySearchTree::util_inorderTraverse(CTreeNode* psRoot, void *pvExtraArgs)
{
	if (psRoot)
	{
		if (psRoot->nextLeft())
			util_inorderTraverse(psRoot->nextLeft(), pvExtraArgs);

		onNodeTraverse(psRoot, pvExtraArgs);

		if (psRoot->nextRight())
			util_inorderTraverse(psRoot->nextRight(), pvExtraArgs);
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
