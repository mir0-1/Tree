#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "CBinarySearchTree.h"

int main()
{
	int key, i, op;
	CBinarySearchTree bst;
	STreeNode* root = (STreeNode*)1515;

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
			bst.insert(key, NULL);
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


	return 0;
}