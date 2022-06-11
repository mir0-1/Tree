#pragma once
#include "STreeNode.h"
#define SSTACKNODE_ARRLEN 3

struct SStackNode
{
	STreeNode* pArrSTnodes[SSTACKNODE_ARRLEN];
	SStackNode* psNext;
};

class CTnStack
{
	private:
		SStackNode* psHead;
		unsigned int uiTotalElementCount;

	public:
		unsigned int push(STreeNode* sNode);
		STreeNode* pop(unsigned int* puiElementsLeft);
		void clear();

		CTnStack();

		~CTnStack();
};

