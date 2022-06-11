#pragma once
#include "STreeNode.h"
#include "CTnStack.h"

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
		CTnStack oTnStack;
		
		STreeNode* newNode(int iNumber, void* pvExtAllocData, bool bUseStack);
		bool delNode_noChildrenCase(STreeNode* psTreeWalker, STreeNode* psTwParent);
		bool delNode_oneChildCase(STreeNode* psTreeWalker);
		bool delNode_twoChildrenCase(STreeNode* psTreeWalker);
		bool delNode(STreeNode* psTreeWalker, STreeNode* psTwParent);
		void inorderTraverse(STreeNode* psRoot);
		STreeNode* walkPathTo(int iNumber, bool bExactMatch, STreeNode** ppsTwParent, bool bUseStack);
		bool util_insert(int iNumber, void* pvExtAllocData, bool bUseStack);
		bool util_remove(int iNumber, bool bUseStack);
	public:
		ENodeMatchType find(int iNumber, bool bExactMatch);
		bool insert(int iNumber, void* pvExtAllocData);
		bool remove(int iNumber);

		void inorderPrint();

		CBinarySearchTree();
};

