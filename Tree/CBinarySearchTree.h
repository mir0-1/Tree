#pragma once
#include "STreeNode.h"
#include "CTnStack.h"

enum ENodeMatchType
{
	EXACT_MATCH,
	CLOSEST_MATCH,
	NO_MATCH
};

class CAvlTree;

class CBinarySearchTree
{
	private:
		STreeNode* psRoot;

		STreeNode* util_rm_dispatchCases(STreeNode* psToBeRmed, STreeNode* psCopyToNode);
		STreeNode* util_rm_caseOneChild(STreeNode* psToBeRmed, STreeNode* psCopyToNode);
		STreeNode* util_rm_noChildren(STreeNode* psToBeRmed, STreeNode *psCopyToNode);
		STreeNode* util_rm_twoChildren(STreeNode* psToBeRmed);

		virtual STreeNode* postOperation(STreeNode* psTreeWalker);
		virtual void onNodeTraverse(STreeNode* psNode, void* pvExtraArgs);
		
		STreeNode* newNode(int iNumber, void* pvAllocExtraData);
		STreeNode* util_insert(STreeNode *psRoot, int iNumber, void* pvAllocExtraData);
		STreeNode* util_remove(STreeNode* psRoot, int iNumber, STreeNode* psCopyToNode);

		void util_inorderTraverse(STreeNode* psRoot, void *pvExtraArgs);

		friend class CAvlTree;
	public:
		//ENodeMatchType find(int iNumber, bool bExactMatch);
		void insert(int iNumber, void* pvExtAllocData);
		void remove(int iNumber);

		void inorderPrint();

		CBinarySearchTree();
};

