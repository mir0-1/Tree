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
		printf("Enter op.\nTREE:\tInsert:0\tDelete:1\tRotateLeft:4\tRotateRight:5\nSTACK:\tPush:2\t\tPop:3\nEXIT:\tExit:-1\nop:");
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

		else if (op == 4)
			bst.t_leftRotate();

		else if (op == 5)
			bst.t_rightRotate();
	}

	bst.inorderPrint();

	return 0;
}