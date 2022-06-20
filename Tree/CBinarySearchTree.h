#pragma once
#include "CTreeNode.h"
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
		CTreeNode* psRoot;

		CTreeNode* util_rm_dispatchCases(CTreeNode* poToBeRmed, CTreeNode* poCopyToNode);
		CTreeNode* util_rm_caseOneChild(CTreeNode* poToBeRmed, CTreeNode* poCopyToNode);
		CTreeNode* util_rm_noChildren(CTreeNode* poToBeRmed, CTreeNode *poCopyToNode);
		CTreeNode* util_rm_twoChildren(CTreeNode* poToBeRmed);

		virtual CTreeNode* postOperation(CTreeNode* poTreeWalker);
		virtual void onNodeTraverse(CTreeNode* poNode, void* pvExtraArgs);
		
		CTreeNode* util_insert(CTreeNode *poRoot, int iNumber, void* pvAllocExtraData);
		CTreeNode* util_remove(CTreeNode* poRoot, int iNumber, CTreeNode* poCopyToNode);

		void util_inorderTraverse(CTreeNode* poRoot, void *pvExtraArgs);

		friend class CAvlTree;
	public:
		//ENodeMatchType find(int iNumber, bool bExactMatch);
		void insert(int iNumber, void* pvExtAllocData);
		void remove(int iNumber);

		void inorderPrint();

		CBinarySearchTree();
};

