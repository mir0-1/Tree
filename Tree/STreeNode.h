#pragma once

struct STreeNode
{
	int iNumber;
	void* pvExtAllocData;
	STreeNode* psLeft;
	STreeNode* psRight;
	unsigned int uiHeight;
};
