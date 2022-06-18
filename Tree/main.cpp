#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "CBinarySearchTree.h"
#include "CAvlTree.h"


int main()
{
	int key, i, op, test;
	CAvlTree bst;
	CTnStack oStack;

	srand(time(NULL));
	key = 0;

	while (true)
	{
		printf("Enter op.\nTREE:\tInsert:0\tDelete:1\tRotateLeft:4\tRotateRight:5\nSTACK:\tPush:2\t\tPop:3\tPeek:6\nEXIT:\tExit:-1\nop:");
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
			printf("Stack push key: ");
			scanf("%d", &key);
			oStack.push((STreeNode*)key);
			printf("Pushed %d on stack\n", key);
		}

		else if (op == 3)
		{
			printf("Stack pop key: ");
			scanf("%d", &key);
			key = (int)oStack.pop(nullptr);
			printf("Popped %d from stack\n");
		}

		else if (op == 6)
		{
			printf("Stack peek depth: ");
			scanf("%d", &key);
			key = (int)oStack.peek(key);
			printf("Stack peek returned %d\n", key);
		}

		else if (op == 4)
			bst.t_leftRotate();

		else if (op == 5)
			bst.t_rightRotate();

		else if (op == 99)
		{
			printf("BREAKPOINT HIT\n");
		}
	}

	bst.inorderPrint();

	return 0;
}