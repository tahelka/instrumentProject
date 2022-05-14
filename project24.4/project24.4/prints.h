#ifndef __PRINTS_H
#define __PRINTS_H

#include "trees.h"
#include <stdio.h>

// Prints trees

// this function prints a tree in order
void printTreeInorder(InstrumentTree tr);
// this function is a helper function for printTreeInorder function
void printTreeInorderHelper(TreeNode* node);

#endif