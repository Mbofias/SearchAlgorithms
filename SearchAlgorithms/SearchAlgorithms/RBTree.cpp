#include "RBTree.h"

//Se intenta a�adir un nuevo nodo al �rbol.
void RBTree::InsertNode(const int value)
{
	//Si no existe un nodo root, el nuevo nodo se convierte en el root del �rbol.
	if (root == nullptr)
	{
		root = new RBNode(value);
		root->color = BLACK;
		return;
	}

	//Se a�ade el nodo al �rbol, dejando que cada nodo se encargue de decidir hacia que direcci�n va.
	RBNode* tmptr = root->AttachNode(value);
	
	//En caso de haber conseguido a�adir el nodo al �rbol, se realizan las comprobaciones necesarias para asegurar que el �rbol cumpla todas sus condiciones.
	if (tmptr != nullptr)
		FixRBTree(tmptr);
}

//Se realiza la busqueda de un nodo en el �rbol.
RBNode* RBTree::SearchNode(const int value)
{
	RBNode* tmp;

	if (root != nullptr)
		tmp = root->Search(value);
	else
		tmp = nullptr;

	//Una vez realizada la b�squeda se imprime el camino.
	PrintPath(tmp);
	return tmp;
}

//Funci�n que Realiza todas las comprobaciones necesarias al a�adir un nuevo nodo, se asegura que el �rbol sigue cumpliendo todas sus condiciones.
void RBTree::FixRBTree(RBNode* node)
{
	//Almacenamos el padre del nodo que vamos a comprobar.
	RBNode* parent;
	//El abuelo.
	RBNode* grandParent;
	//Y el t�o.
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
					//Si la forma en la que queda el �rbol �s de flecha (abuelo -> hijo_izquierdo == padre -> hizo_derecho == nodo)
					//Soluci�n 3-A
					if (node == parent->rightChild)
						RotateLeft(parent);
					//Si la forma en la que queda el �rbol �s de l�nea (abuelo -> hijo_izquierdo == padre -> hizo_izquierdo == nodo)
					//Soluci�n 3-B
					else
					{
						RotateRight(grandParent);
						parent->color = BLACK;
						grandParent->color = RED;
					}
					//Se asigna al padre como el nuevo nodo a comprobar.
					node = parent;
				}
				//Soluci�n 2
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

//Se imprime el camino que se ha seguido al realizar la b�squeda de un nodo.
void RBTree::PrintPath(RBNode* node)
{
	if (node != nullptr)
		std::cout << "Se ha encontrado el nodo desado siguiendo el siguiente camino: " << node->GetPath() << std::endl;
	else
		std::cout << "No se ha encontrado ningun nodo con ese valor." << std::endl;
}

//Se rota un nodo hacia la izquierda, y realizan los cambios necesarios para mantener la estructura del �rbol.
void RBTree::RotateLeft(RBNode* node)
{
	//El hijo izquierdo ser� el nuevo padre.
	RBNode* newParent = node->rightChild;

	//El hijo izquierdo del nuevo padre ser� el hijo derecho del nodo rotado.
	node->rightChild = newParent->leftChild;

	//Si el nuevo hijo derecho no est� vac�o, se le asigna el nodo rotado como su padre.
	if (node->rightChild != nullptr)
		node->rightChild->parent = node;

	//El nuevo padre del nodo rotado tendr� como padre el antiguo padre del nodo rotado, es decir, su antiguo abuelo.
	newParent->parent = node->parent;

	//Si el padre antiguo no est� vac�o:
	if (node->parent != nullptr)
		//Si el nodo rotado era el hijo izquierdo, el nuevo padre ocupa su lugar como hijo izquierdo.
		if (node->parent->leftChild == node)
			node->parent->leftChild = newParent;
		//En caso de ser el hijo derecho, el nuevo padre ocupa el puesto de hijo derecho.
		else
			node->parent->rightChild = newParent;
	//Si el padre era nullptr, significa que se trataba del nodo root, as� que el nuevo padre se convierte en el nodo root del �rbol.
	else
		root = newParent;
	//El nodo rotado ocupa el puesto del hijo izquierdo para el nuevo padre.
	newParent->leftChild = node;
	//El padre del nodo rotado pasa a ser su antiguo hijo derecho.
	node->parent = newParent;
}

//Se rota un nodo hacia la izquierda, y realizan los cambios necesarios para mantener la estructura del �rbol.
//En esencia es la misma funci�n que al rotar un nodo a la izquierda, alterando las direcciones.
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