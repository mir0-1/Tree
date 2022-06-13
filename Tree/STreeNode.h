#pragma once

struct STreeNode
{
	int iNumber;
	void* pvExtAllocData;
	STreeNode* psLeft;
	STreeNode* psRight;
	union
	{
		unsigned int uiHeight;
		STreeNode* psPrev;
	} uMetadata;
};
