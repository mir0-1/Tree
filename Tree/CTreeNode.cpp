#include "CTreeNode.h"

CTreeNode* CTreeNode::nextLeft()
{
	return poLeft;
}

CTreeNode* CTreeNode::nextRight()
{
	return poRight;
}

bool CTreeNode::nextLeft(CTreeNode* poNewNode)
{
	poLeft = poNewNode;
	return true;
}

bool CTreeNode::nextRight(CTreeNode* poNewNode)
{
	poRight = poNewNode;
	return true;
}

CTreeNode::CTreeNode(int iInNumber, void* pvInExtAllocData)
{
	iNumber = iInNumber;
	pvExtAllocData = pvInExtAllocData;
	poLeft = nullptr;
	poRight = nullptr;
}
