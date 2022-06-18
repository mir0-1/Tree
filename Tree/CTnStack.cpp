#include "CTnStack.h"
#include <stdio.h>

unsigned int CTnStack::push(STreeNode** ppsNode)
{
	if (uiTotalElementCount % SSTACKNODE_ARRLEN == 0)
	{
		SStackNode* psNode = new SStackNode;
		psNode->psNext = psHead;
		psHead = psNode;
	}

	psHead->pArrSTnodes[uiTotalElementCount % SSTACKNODE_ARRLEN] = ppsNode;
	uiTotalElementCount++;

	return uiTotalElementCount;
}

STreeNode** CTnStack::pop(unsigned int* puiElementsLeft)
{
	if (psHead == nullptr)
	{
		if (puiElementsLeft)
			* puiElementsLeft = uiTotalElementCount;
		return nullptr;
	}

	STreeNode** ppsPopped = nullptr;
	SStackNode* psEmptySn;

	uiTotalElementCount--;
	ppsPopped = psHead->pArrSTnodes[uiTotalElementCount % SSTACKNODE_ARRLEN];

	if (uiTotalElementCount % SSTACKNODE_ARRLEN == 0)
	{
		psEmptySn = psHead;
		psHead = psHead->psNext;
		delete psEmptySn;
	}

	if (puiElementsLeft)
		*puiElementsLeft = uiTotalElementCount;

	return ppsPopped;
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
