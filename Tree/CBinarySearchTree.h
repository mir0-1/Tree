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
		enum EWalkReason
		{
			DELETE,
			DELETE_INORDER,
			INSERT,
			FIND_CLOSEST,
			FIND_EXACT,
		};

		STreeNode* psRoot;
		CTnStack *poTnStack;
		
		STreeNode* newNode(int iNumber, void* pvExtAllocData);
		bool delNode_noChildrenCase(STreeNode* psTreeWalker, STreeNode* psTwParent);
		bool delNode_oneChildCase(STreeNode* psTreeWalker);
		bool delNode_twoChildrenCase(STreeNode* psTreeWalker);
		bool delNode(STreeNode* psTreeWalker, STreeNode* psTwParent);
		void inorderTraverse(STreeNode* psRoot);
		STreeNode* walkPathFromTo(STreeNode* psStart, int iNumber, STreeNode** ppsTwParent, EWalkReason eReason);

		friend class CAvlTree;
	public:
		ENodeMatchType find(int iNumber, bool bExactMatch);
		bool insert(int iNumber, void* pvExtAllocData);
		bool remove(int iNumber);

		void inorderPrint();

		CBinarySearchTree();
};

