#pragma once

struct STreeNode
{
	int iNumber;
	void* pvExtAllocData;
	int iPageGroupNumber;
	STreeNode* psLeft;
	STreeNode* psRight;
	unsigned int uiHeight;
};
