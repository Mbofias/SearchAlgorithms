#include "Quadtree.h"

//Esta funci�n sirve para insertar un nodo en el Quadtree
void Quadtree::Insert(QTNode* node)
{
	//Comprobamos que sea un nodo existente.
	if (node == nullptr)
	{
		delete node;
		return;
	}

	//Comprobamos que el nodo se encuentra dentro de los l�mites.
	if (!IsInsideBounds(node->position))
	{
		delete node;
		return;
	}

	//Comprobamos si ya no se pude seguir dividiendo el espacio en celdas mas peque�as.
	if (abs(bounds.topLeft.x - bounds.botRight.x) <= 1 && abs(bounds.topLeft.y - bounds.botRight.y) <= 1)
	{
		//Si el sub-�rbol indivisible no tiene un nodo asignado, quiere decir que se trata de un nuevo sub-�rbol, as� que le asignamos este nodo.
		if (node == nullptr)
			this->node = node;
		else
			delete node;
		return;
	}

	//Comprobamos si se encuentra en la mitad izquierda de los l�mites.
	if ((bounds.topLeft.x + bounds.botRight.x) / 2 >= node->position.x)
	{
		//En caso de encontrarse en la mitad superior de los l�mites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= node->position.y)
		{
			//Si no esta dividida, creamos el sub-�rbol que contendr� dicho nodo.
			if (topLeft == nullptr)
			{
				Vector2D start = Vector2D(bounds.topLeft.x, bounds.topLeft.y);
				Vector2D end = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Bounds2D size = Bounds2D(start, end);
				topLeft = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-�rbol.
			topLeft->Insert(node);
		}
		//En caso de encontrarse en la mitad inferior de los l�mites.
		else
		{
			//Si no esta dividida, creamos el sub-�rbol que contendr� dicho nodo.
			if (botRight == nullptr)
			{
				Vector2D start = Vector2D(bounds.topLeft.x, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Vector2D end = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, bounds.botRight.y);
				Bounds2D size = Bounds2D(start, end);
				botRight = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-�rbol.
			botRight->Insert(node);
		}
	}
	//En caso de encontrarse en la mitad derecha de los l�mites
	else
	{
		//En caso de encontrarse en la mitad superior de los l�mites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= node->position.y)
		{
			//Si no esta dividida, creamos el sub-�rbol que contendr� dicho nodo.
			if (topRight == nullptr)
			{
				Vector2D start = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, bounds.topLeft.y);
				Vector2D end = Vector2D(bounds.botRight.x, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Bounds2D size = Bounds2D(start, end);
				topRight = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-�rbol.
			topRight->Insert(node);
		}
		//En caso de encontrarse en la mitad inferior de los l�mites.
		else
		{
			//Si no esta dividida, creamos el sub-�rbol que contendr� dicho nodo.
			if (botRight == nullptr)
			{
				Vector2D start = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Vector2D end = Vector2D(bounds.botRight.x, bounds.botRight.y);
				Bounds2D size = Bounds2D(start, end);
				botRight = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-�rbol.
			botRight->Insert(node);
		}
	}
}

QTNode* const Quadtree::Search(const Vector2D point)
{
	//Comprobamos que el punto se encuentra dentro de los l�mites.
	if (!IsInsideBounds(point))
		return nullptr;

	//Si el sub-�rbol en el que estamos tiene un nodo asignado
	//y, por lo tanto, no se puede dividir m�s,
	//devolvemos el nodo asignado a este sub-�rbol
	if (node != nullptr)
		return node;

	//Comprobamos si se encuentra en la mitad izquierda de los l�mites.
	if ((bounds.topLeft.x + bounds.botRight.x) / 2 >= point.x)
	{
		//En caso de encontrarse en la mitad superior de los l�mites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= point.y)
		{
			//Si no existe un sub-�rbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (topLeft == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-�rbol.
			return topLeft->Search(point);
		}
		//En caso de encontrarse en la mitad inferior de los l�mites.
		else
		{
			//Si no existe un sub-�rbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (botLeft == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-�rbol.
			return botLeft->Search(point);
		}
	}
	else
	{
		//En caso de encontrarse en la mitad superior de los l�mites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= point.y)
		{
			//Si no existe un sub-�rbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (topRight == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-�rbol.
			return topRight->Search(point);
		}
		//En caso de encontrarse en la mitad inferior de los l�mites.
		else
		{
			//Si no existe un sub-�rbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (botRight == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-�rbol.
			return botRight->Search(point);
		}
	}
}
