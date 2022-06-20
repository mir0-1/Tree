#pragma once

class CTreeNode
{
	private:
		int iNumber;
		void* pvExtAllocData;
		int iPageGroupNumber;
		CTreeNode* poLeft;
		CTreeNode* poRight;
		unsigned int uiHeight;

		friend class CBinarySearchTree;
		friend class CAvlTree;
	public:
		CTreeNode* nextLeft();
		CTreeNode* nextRight();
		bool nextLeft(CTreeNode* poNewNode);
		bool nextRight(CTreeNode* poNewNode);

		CTreeNode(int iInNumber, void* pvInExtAllocData);
};
