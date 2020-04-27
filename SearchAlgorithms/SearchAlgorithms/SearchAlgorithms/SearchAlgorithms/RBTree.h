#pragma once
#include "RBNode.h"

class RBTree
{
	RBNode *root;

public:
	_forceinline RBTree() { root = nullptr; }
	__forceinline ~RBTree() { root->ForcedTreeDelete(); delete root; }
	void InsertNode(const int value); 
	RBNode* SearchNode(const int value);
	void PrintTree() { root->PrintTree(); }
private:
	void FixRBTree(RBNode *node);
	void PrintPath(RBNode* node);
	void RotateLeft(RBNode* node);
	void RotateRight(RBNode* node);
};

