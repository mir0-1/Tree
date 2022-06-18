#include "CTnStack.h"
#include <stdio.h>

unsigned int CTnStack::push(STreeNode* psNode)
{
	if (uiTotalElementCount % SSTACKNODE_ARRLEN == 0)
	{
		SStackNode* psNode = new SStackNode;
		psNode->psNext = psHead;
		psHead = psNode;
	}

	psHead->pArrSTnodes[uiTotalElementCount % SSTACKNODE_ARRLEN] = psNode;
	uiTotalElementCount++;

	return uiTotalElementCount;
}

STreeNode* CTnStack::pop(unsigned int* puiElementsLeft)
{
	if (psHead == nullptr)
	{
		if (puiElementsLeft)
			* puiElementsLeft = uiTotalElementCount;
		return nullptr;
	}

	STreeNode* psPopped = nullptr;
	SStackNode* psEmptySn;

	uiTotalElementCount--;
	psPopped = psHead->pArrSTnodes[uiTotalElementCount % SSTACKNODE_ARRLEN];

	if (uiTotalElementCount % SSTACKNODE_ARRLEN == 0)
	{
		psEmptySn = psHead;
		psHead = psHead->psNext;
		delete psEmptySn;
	}

	if (puiElementsLeft)
		*puiElementsLeft = uiTotalElementCount;

	return psPopped;
}

STreeNode* CTnStack::peek(unsigned int uiDepth)
{
	SStackNode* psStackWalker = psHead;

	if (uiDepth >= uiTotalElementCount || uiTotalElementCount == 0)
		return nullptr;

	int uiCurrentArrLength = uiTotalElementCount % SSTACKNODE_ARRLEN;

	if (uiCurrentArrLength == 0)
		uiCurrentArrLength = SSTACKNODE_ARRLEN;

	while (uiDepth > uiCurrentArrLength-1 && psStackWalker->psNext)
	{
		psStackWalker = psStackWalker->psNext;
		uiDepth -= uiCurrentArrLength;
		uiCurrentArrLength = SSTACKNODE_ARRLEN;
	}

	return psStackWalker->pArrSTnodes[uiCurrentArrLength - 1 - uiDepth];
}

void CTnStack::clear()
{
	SStackNode* psTemp;

	while (psHead)
	{
		psTemp = psHead;
		psHead = psHead->psNext;
		delete psTemp;
	}

	uiTotalElementCount = 0;
}

CTnStack::CTnStack()
{
	psHead = nullptr;
	uiTotalElementCount = 0;
}

CTnStack::~CTnStack()
{
	clear();
}
