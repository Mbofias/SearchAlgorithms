#include "RBTree.h"

void RBTree::InsertNode(const int value)
{
	if (root == nullptr)
	{
		root = new RBNode(value);
		root->color = BLACK;
		return;
	}

	RBNode* tmptr = root->AttachNode(value);
	
	if (tmptr != nullptr)
		FixRBTree(tmptr);
}

RBNode* RBTree::SearchNode(const int value)
{
	RBNode* tmp;

	if (root != nullptr)
		tmp = root->Search(value);
	else
		tmp = nullptr;

	PrintPath(tmp);
	return tmp;
}

void RBTree::FixRBTree(RBNode* node)
{
	RBNode* parent;
	RBNode* grandParent;
	RBNode* uncle;

	if (node->parent != nullptr)
	{
		while (node->parent->color == RED)
		{
			parent = node->parent;
			grandParent = node->parent->parent;
			if (parent == grandParent->leftChild)
			{
				uncle = grandParent->rightChild;
				if (uncle == nullptr || uncle->color == BLACK)
				{
					if (node == parent->rightChild)
						RotateLeft(parent);
					else
					{
						RotateRight(grandParent);
						parent->color = BLACK;
						grandParent->color = RED;
					}
					node = parent;
				}
				else
				{
					uncle->color = BLACK;
					parent->color = BLACK;
					grandParent->color = RED;
					node = grandParent;
				}
			}
			else
			{
				uncle = grandParent->leftChild;
				if (uncle == nullptr || uncle->color == BLACK)
				{
					if (node == parent->leftChild)
						RotateRight(parent);
					else
					{
						RotateLeft(grandParent);
						parent->color = BLACK;
						grandParent->color = RED;
					}
					node = parent;
				}
				else
				{
					uncle->color = BLACK;
					parent->color = BLACK;
					grandParent->color = RED;
					node = grandParent;
				}
			}
			if (node->parent == nullptr)
				break;
		}
	}
	root->color = BLACK;
}

void RBTree::PrintPath(RBNode* node)
{
	if (node != nullptr)
		std::cout << "Se ha encontrado el nodo desado siguiendo el siguiente camino: " << node->GetPath() << std::endl;
	else
		std::cout << "No se ha encontrado ningun nodo con ese valor." << std::endl;
}

void RBTree::RotateLeft(RBNode* node)
{
	RBNode* newParent = node->rightChild;

	node->rightChild = newParent->leftChild;

	if (node->rightChild != nullptr)
		node->rightChild->parent = node;

	newParent->parent = node->parent;

	if (node->parent != nullptr)
		if (node->parent->leftChild == node)
			node->parent->leftChild = newParent;
		else
			node->parent->rightChild = newParent;
	else
		root = newParent;

	newParent->leftChild = node;
	node->parent = newParent;
}

void RBTree::RotateRight(RBNode* node)
{
	RBNode* newParent = node->leftChild;

	node->leftChild = newParent->rightChild;

	if (node->leftChild != nullptr)
		node->leftChild->parent = node;

	newParent->parent = node->parent;

	if (node->parent != nullptr)
		if (node->parent->leftChild == node)
			node->parent->leftChild = newParent;
		else
			node->parent->rightChild = newParent;
	else
		root = newParent;

	newParent->rightChild = node;
	node->parent = newParent;
}