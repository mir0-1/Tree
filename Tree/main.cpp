#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "CBinarySearchTree.h"
#include "CAvlTree.h"


int main()
{
	int key, i, op, test;
	CBinarySearchTree bst;
	CTnStack oStack;

	srand(time(NULL));
	key = 0;
	
	while (true)
	{
		printf("Enter op.\nTREE:\tInsert:0\tDelete:1\nSTACK:\tPush:2\t\tPop:3\nEXIT:\tExit:-1\nop:");
		scanf("%d", &op);
		if (op == -1)
			break;
		if (op == 0)
		{
			printf("insert key:");
			scanf("%d", &key);
			bst.insert(key, nullptr);
			printf("Inserted %d to BST\n", key);
		}

		else if (op == 1)
		{
			printf("delete key:");
			scanf("%d", &key);
			bst.remove(key);
			printf("Removed %d from BST\n", key);
		}

		else if (op == 2)
		{
			printf("push key: ");
			scanf("%d", &key);
			oStack.push((STreeNode*)key);
		}

		else if (op == 3)
		{
			oStack.pop(nullptr);
		}
	}

	bst.inorderPrint();

	return 0;
}