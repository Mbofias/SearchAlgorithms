#pragma once
#include <iostream>
#include <string>
#include <vector>

enum EColor { BLACK, RED };

struct RBNode {
	//Todos los nodos contienen:
	//Un valor
	int value;
	//El color
	EColor color;
	//Un puntero para acceder rapidamente a cualquiera de sus hijos o a su padre.
	RBNode *leftChild, *rightChild, *parent;

	//Constructor, por defecto los nodos siempre empiezan siendo rojos.
	RBNode(const int value) {
		this->value = value;
		this->color = RED;
		leftChild = nullptr;
		rightChild = nullptr;
		parent = nullptr;
	}

	//Función que elimina en cascada el árbol rojo/negro. Funcionaría igual haciendo esta función en el destructor.
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

	//Función que añade el nodo al árbol, devolviendo el nodo añadido.
	RBNode* AttachNode(const int value) {
		//Se comprueba si el nodo va hacia la izquierda.
		if (value < this->value)
			if (leftChild == nullptr)
			{
				//Se iguala al hijo de la izquierda en caso de que este sea nulo.
				leftChild = new RBNode(value);
				leftChild->parent = this;
				return leftChild;
			}
			else
				//En caso de estar el nodo ocupado se le encarga a dicho hijo que siga intentando asignar el nodo.
				return leftChild->AttachNode(value);
		//Se realiza la misma comprobación hacia la derecha.
		if (value > this->value)
			if (rightChild == nullptr)
			{
				rightChild = new RBNode(value);
				rightChild->parent = this;
				return rightChild;
			}
			else
				return rightChild->AttachNode(value);
		//En caso de tratarse de un valor ya existente en el árbol devuelve nullptr y no se asigna el nodo.
		return nullptr;
	}
	
	//Función que permite buscar un nodo en el árbol.
	RBNode* Search(const int value) {
		//Si este nodo contiene el valor buscado, se trata de este nodo, así que se devuelve a si mismo.
		if (value == this->value)
			return this;
		//En caso de ser un valor mas pequeño se comprueba el hijo de la izquierda.
		if (value < this->value)
			//Si el hijo no existe, significa que el valor no está en el árbol, devuelve nullptr.
			if (leftChild == nullptr)
				return nullptr;
			//Si el hijo existe le encargamos realizar las mismas comprobaciones al hijo.
			else
				return leftChild->Search(value);
		//Se realizan las mismas comprobaciones con el hijo de la derecha.
		else
			if (rightChild == nullptr)
				return nullptr;
			else
				return rightChild->Search(value);
	}

	//Imprime todo el camino que realiza una busqueda desde el nodo root hasta el nodo actual, pasando por los nodos recorridos.
	std::string GetPath() {
		if (parent != nullptr)
			return parent->GetPath() + " -> " + std::to_string(value);
		else
			return std::to_string(value);
	}

	//Imprime el árbol entero (si este método se usa desde el root) o sub-árbol empezando por este nodo (si este método se usa desde otro nodo).
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