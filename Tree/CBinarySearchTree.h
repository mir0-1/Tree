#pragma once

struct STreeNode
{
	int iNumber;
	void* pvExtAllocData;
	STreeNode* psLeft;
	STreeNode* psRight;
};

enum ENodeMatchType
{
	EXACT_MATCH,
	CLOSEST_MATCH,
	NO_MATCH
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
		void inorderTraverse(STreeNode* psRoot);
		STreeNode* walkPathTo(int iNumber, bool bExactMatch, STreeNode** ppsTwParent);

		virtual void visitNode(STreeNode* psTreeWalker);
	public:
		bool insert(int iNumber, void* pvExtAllocData);
		bool remove(int iNumber);
		ENodeMatchType find(int iNumber, bool bExactMatch);

		void inorderPrint();

		CBinarySearchTree();
};

