#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "CBinarySearchTree.h"

void visitNode(STreeNode* psNode)
{
	printf("Visited node with number %d\n", psNode->iNumber);
}

int main()
{
	int key, i, op;
	CBinarySearchTree bst;

	srand(time(NULL));
	key = 0;
	
	while (true)
	{
		printf("Enter op. Insert:0\tDelete:1\tExit:2\n");
		printf("op:");
		scanf("%d", &op);
		if (op == 2)
			break;
		if (op == 0)
		{
			printf("insert key:");
			scanf("%d", &key);
			bst.insert(key, NULL, visitNode);
			printf("Inserted %d to BST\n", key);
		}

		else if (op == 1)
		{
			printf("delete key:");
			scanf("%d", &key);
			bst.remove(key);
			printf("Removed %d from BST\n", key);
		}
	}

	bst.inorderPrint();

	return 0;
}