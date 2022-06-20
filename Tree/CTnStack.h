#pragma once
#include "CTreeNode.h"
#define SSTACKNODE_ARRLEN 128

struct SStackNode
{
	CTreeNode* pArrSTnodes[SSTACKNODE_ARRLEN];
	SStackNode* psNext;
};

class CTnStack
{
	private:
		SStackNode* psHead;
		unsigned int uiTotalElementCount;

	public:
		unsigned int push(CTreeNode* sNode);
		CTreeNode* pop(unsigned int* puiElementsLeft);
		CTreeNode* peek(unsigned int uiDepth);
		void clear();

		CTnStack();

		~CTnStack();
};