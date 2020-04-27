#pragma once
#include <iostream>
#include <string>
#include <vector>

enum EColor { BLACK, RED };

struct RBNode {
	int value;
	EColor color;
	RBNode *leftChild, *rightChild, *parent;

	RBNode(const int value) {
		this->value = value;
		this->color = RED;
		leftChild = nullptr;
		rightChild = nullptr;
		parent = nullptr;
	}

	void ForcedTreeDelete() {
		if (leftChild != nullptr)
		{
			leftChild->ForcedTreeDelete();
			delete leftChild;
			leftChild = nullptr;
		}
		if (rightChild != nullptr)
		{
			rightChild->ForcedTreeDelete();
			delete rightChild;
			rightChild = nullptr;
		}
	}

	RBNode* AttachNode(const int value) {
		if (value < this->value)
			if (leftChild == nullptr)
			{
				leftChild = new RBNode(value);
				leftChild->parent = this;
				return leftChild;
			}
			else
				return leftChild->AttachNode(value);
		if (value > this->value)
			if (rightChild == nullptr)
			{
				rightChild = new RBNode(value);
				rightChild->parent = this;
				return rightChild;
			}
			else
				return rightChild->AttachNode(value);
		return nullptr;
	}
	
	RBNode* Search(const int value) {
		if (value == this->value)
			return this;

		if (value < this->value)
			if (leftChild == nullptr)
				return nullptr;
			else
				return leftChild->Search(value);
		else
			if (rightChild == nullptr)
				return nullptr;
			else
				return rightChild->Search(value);
	}

	std::string GetPath() {
		if (parent != nullptr)
			return parent->GetPath() + " -> " + std::to_string(value);
		else
			return std::to_string(value);
	}

	void PrintTree() {
		std::cout << "NODO: " << value << " COLOR: ";

		switch (color)
		{
		case RED:
			std::cout << "ROJO"<< std::endl;
			break;
		case BLACK:
			std::cout << "NEGRO" << std::endl;
			break;
		default:break;
		}

		if (parent != nullptr)
			std::cout << "\t PADRE: " << parent->value << std::endl;

		if (leftChild != nullptr)
			std::cout << "\t HIJO A LA IZQUIERDA: " << leftChild->value << std::endl;

		if (rightChild != nullptr)
			std::cout << "\t HIJO A LA DERECHA: " << rightChild->value << std::endl;

		if (leftChild != nullptr)
			leftChild->PrintTree();

		if (rightChild != nullptr)
			rightChild->PrintTree();
	}
};