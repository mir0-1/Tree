#pragma once

struct STreeNode
{
	int iNumber;
	void* pvExtAllocData;
	STreeNode* psLeft;
	STreeNode* psRight;
};


class CBinarySearchTree
{
	private:
		STreeNode* psRoot;
		
		STreeNode* newNode(int iNumber, void* pvExtAllocData);
		bool delNode_noChildrenCase(STreeNode* psTreeWalker, STreeNode* psTwParent);
		bool delNode_oneChildCase(STreeNode* psTreeWalker);
		bool delNode_twoChildrenCase(STreeNode* psTreeWalker);
		bool delNode(STreeNode* psTreeWalker, STreeNode* psTwParent);

	public:
		bool insert(int iNumber, void* pvExtAllocData);
		STreeNode* find(int iNumber, bool bExactMatch, STreeNode** ppsTwParent);
		bool remove(int iNumber);

		CBinarySearchTree();
};

