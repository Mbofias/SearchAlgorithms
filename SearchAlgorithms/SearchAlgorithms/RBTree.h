#pragma once
#include "RBNode.h"

class RBTree
{
	RBNode *root;

public:
	//Constructor de un �rbol rojo-negro vac�o.
	__forceinline RBTree() { root = nullptr; }
	//El destructor se asegura de liberar la memoria usada por todos los nodos del �rbol.
	__forceinline ~RBTree() { root->ForcedTreeDelete(); delete root; }
	//A�ade un nuevo nodo al �rbol.
	void InsertNode(const int value);
	//Busca el nodo con el valor que se pasa por par�metro.
	RBNode* SearchNode(const int value);
	//Funci�n que imprime el �rbol entero, siempre empieza en el root.
	void PrintTree() { root->PrintTree(); }
private:
	//Funci�n que Realiza todas las comprobaciones necesarias al a�adir un nuevo nodo, se asegura que el �rbol sigue cumpliendo todas sus condiciones.
	void FixRBTree(RBNode *node);
	//Imprime el camino a seguir buscando un nodo.
	void PrintPath(RBNode* node);
	//Rotaci�n hacia la izquierda de un nodo.
	void RotateLeft(RBNode* node);
	//Rotaci�n hacia la derecha de un nodo.
	void RotateRight(RBNode* node);
};

