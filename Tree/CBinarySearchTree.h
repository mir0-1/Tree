#pragma once
#include "STreeNode.h"
#include "CTnStack.h"

enum ENodeMatchType
{
	EXACT_MATCH,
	CLOSEST_MATCH,
	NO_MATCH
};

extern class CAvlTree;

class CBinarySearchTree
{
	private:
		STreeNode* psRoot;
		CTnStack *poTnStack;
		bool bBackwalk;
		
		STreeNode* newNode(int iNumber, void* pvExtAllocData);
		bool delNode_noChildrenCase(STreeNode* psTreeWalker, STreeNode* psTwParent);
		bool delNode_oneChildCase(STreeNode* psTreeWalker);
		bool delNode_twoChildrenCase(STreeNode* psTreeWalker);
		bool delNode(STreeNode* psTreeWalker, STreeNode* psTwParent);
		void inorderTraverse(STreeNode* psRoot);
		STreeNode* walkPathTo(int iNumber, bool bExactMatch, STreeNode** ppsTwParent, bool bIsSearchOnly);

		friend class CAvlTree;
	public:
		ENodeMatchType find(int iNumber, bool bExactMatch);
		STreeNode* util_insert(int iNumber, void* pvExtAllocData);
		bool remove(int iNumber);

		void inorderPrint();

		CBinarySearchTree();
};

