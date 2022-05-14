
#include "prints.h"

void printTreeInorder(InstrumentTree tr)
{
	printTreeInorderHelper(tr.root);
	printf("\n");
}

void printTreeInorderHelper(TreeNode* node)
{
	if (node == NULL) {
		return;
	}

	else {
		printTreeInorderHelper(node->left);
		printf("%s ", node->instrument);
		printTreeInorderHelper(node->right);
	}
}
