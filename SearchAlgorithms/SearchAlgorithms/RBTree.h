#pragma once
#include "RBNode.h"

class RBTree
{
	RBNode *root;

public:
	//Constructor de un árbol rojo-negro vacío.
	__forceinline RBTree() { root = nullptr; }
	//El destructor se asegura de liberar la memoria usada por todos los nodos del árbol.
	__forceinline ~RBTree() { root->ForcedTreeDelete(); delete root; }
	//Añade un nuevo nodo al árbol.
	void InsertNode(const int value);
	//Busca el nodo con el valor que se pasa por parámetro.
	RBNode* SearchNode(const int value);
	//Función que imprime el árbol entero, siempre empieza en el root.
	void PrintTree() { root->PrintTree(); }
private:
	//Función que Realiza todas las comprobaciones necesarias al añadir un nuevo nodo, se asegura que el árbol sigue cumpliendo todas sus condiciones.
	void FixRBTree(RBNode *node);
	//Imprime el camino a seguir buscando un nodo.
	void PrintPath(RBNode* node);
	//Rotación hacia la izquierda de un nodo.
	void RotateLeft(RBNode* node);
	//Rotación hacia la derecha de un nodo.
	void RotateRight(RBNode* node);
};

