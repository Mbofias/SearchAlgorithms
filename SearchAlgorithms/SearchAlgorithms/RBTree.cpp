#include "RBTree.h"

//Se intenta añadir un nuevo nodo al árbol.
void RBTree::InsertNode(const int value)
{
	//Si no existe un nodo root, el nuevo nodo se convierte en el root del árbol.
	if (root == nullptr)
	{
		root = new RBNode(value);
		root->color = BLACK;
		return;
	}

	//Se añade el nodo al árbol, dejando que cada nodo se encargue de decidir hacia que dirección va.
	RBNode* tmptr = root->AttachNode(value);
	
	//En caso de haber conseguido añadir el nodo al árbol, se realizan las comprobaciones necesarias para asegurar que el árbol cumpla todas sus condiciones.
	if (tmptr != nullptr)
		FixRBTree(tmptr);
}

//Se realiza la busqueda de un nodo en el árbol.
RBNode* RBTree::SearchNode(const int value)
{
	RBNode* tmp;

	if (root != nullptr)
		tmp = root->Search(value);
	else
		tmp = nullptr;

	//Una vez realizada la búsqueda se imprime el camino.
	PrintPath(tmp);
	return tmp;
}

//Función que Realiza todas las comprobaciones necesarias al añadir un nuevo nodo, se asegura que el árbol sigue cumpliendo todas sus condiciones.
void RBTree::FixRBTree(RBNode* node)
{
	//Almacenamos el padre del nodo que vamos a comprobar.
	RBNode* parent;
	//El abuelo.
	RBNode* grandParent;
	//Y el tío.
	RBNode* uncle;

	//Comprobamos si se trata del nodo root.
	if (node->parent != nullptr)
	{
		//Mientras el padre del nodo sea de color rojo se ejecuta el siguiente bucle.
		while (node->parent->color == RED)
		{
			parent = node->parent;
			grandParent = node->parent->parent;
			//Si el padre es el hijo izquierdo del abuelo se hacen las comprobaciones siguientes. 
			if (parent == grandParent->leftChild)
			{
				uncle = grandParent->rightChild;
				//Si el tio es negro o NIL:
				if (uncle == nullptr || uncle->color == BLACK)
				{
					//Si la forma en la que queda el árbol és de flecha (abuelo -> hijo_izquierdo == padre -> hizo_derecho == nodo)
					//Solución 3-A
					if (node == parent->rightChild)
						RotateLeft(parent);
					//Si la forma en la que queda el árbol és de línea (abuelo -> hijo_izquierdo == padre -> hizo_izquierdo == nodo)
					//Solución 3-B
					else
					{
						RotateRight(grandParent);
						parent->color = BLACK;
						grandParent->color = RED;
					}
					//Se asigna al padre como el nuevo nodo a comprobar.
					node = parent;
				}
				//Solución 2
				else
				{
					uncle->color = BLACK;
					parent->color = BLACK;
					grandParent->color = RED;
					//En este caso se asigna al abuelo como el nuevo nodo a comprobar.
					node = grandParent;
				}
			}
			//Si el padre es el hijo derecho del abuelo se hacen las comprobaciones siguientes. 
			//Funciona igual que si el padre fuera el hijo izquierdo del abuelo, invirtiendo las direcciones.
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
	//El root siempre acaba en negro.
	root->color = BLACK;
}

//Se imprime el camino que se ha seguido al realizar la búsqueda de un nodo.
void RBTree::PrintPath(RBNode* node)
{
	if (node != nullptr)
		std::cout << "Se ha encontrado el nodo desado siguiendo el siguiente camino: " << node->GetPath() << std::endl;
	else
		std::cout << "No se ha encontrado ningun nodo con ese valor." << std::endl;
}

//Se rota un nodo hacia la izquierda, y realizan los cambios necesarios para mantener la estructura del árbol.
void RBTree::RotateLeft(RBNode* node)
{
	//El hijo izquierdo será el nuevo padre.
	RBNode* newParent = node->rightChild;

	//El hijo izquierdo del nuevo padre será el hijo derecho del nodo rotado.
	node->rightChild = newParent->leftChild;

	//Si el nuevo hijo derecho no está vacío, se le asigna el nodo rotado como su padre.
	if (node->rightChild != nullptr)
		node->rightChild->parent = node;

	//El nuevo padre del nodo rotado tendrá como padre el antiguo padre del nodo rotado, es decir, su antiguo abuelo.
	newParent->parent = node->parent;

	//Si el padre antiguo no está vacío:
	if (node->parent != nullptr)
		//Si el nodo rotado era el hijo izquierdo, el nuevo padre ocupa su lugar como hijo izquierdo.
		if (node->parent->leftChild == node)
			node->parent->leftChild = newParent;
		//En caso de ser el hijo derecho, el nuevo padre ocupa el puesto de hijo derecho.
		else
			node->parent->rightChild = newParent;
	//Si el padre era nullptr, significa que se trataba del nodo root, así que el nuevo padre se convierte en el nodo root del árbol.
	else
		root = newParent;
	//El nodo rotado ocupa el puesto del hijo izquierdo para el nuevo padre.
	newParent->leftChild = node;
	//El padre del nodo rotado pasa a ser su antiguo hijo derecho.
	node->parent = newParent;
}

//Se rota un nodo hacia la izquierda, y realizan los cambios necesarios para mantener la estructura del árbol.
//En esencia es la misma función que al rotar un nodo a la izquierda, alterando las direcciones.
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