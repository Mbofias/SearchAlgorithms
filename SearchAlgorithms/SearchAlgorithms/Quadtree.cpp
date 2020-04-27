#include "Quadtree.h"

//Esta función sirve para insertar un nodo en el Quadtree
void Quadtree::Insert(QTNode* node)
{
	//Comprobamos que sea un nodo existente.
	if (node == nullptr)
	{
		delete node;
		return;
	}

	//Comprobamos que el nodo se encuentra dentro de los límites.
	if (!IsInsideBounds(node->position))
	{
		delete node;
		return;
	}

	//Comprobamos si ya no se pude seguir dividiendo el espacio en celdas mas pequeñas.
	if (abs(bounds.topLeft.x - bounds.botRight.x) <= 1 && abs(bounds.topLeft.y - bounds.botRight.y) <= 1)
	{
		//Si el sub-árbol indivisible no tiene un nodo asignado, quiere decir que se trata de un nuevo sub-árbol, así que le asignamos este nodo.
		if (node == nullptr)
			this->node = node;
		else
			delete node;
		return;
	}

	//Comprobamos si se encuentra en la mitad izquierda de los límites.
	if ((bounds.topLeft.x + bounds.botRight.x) / 2 >= node->position.x)
	{
		//En caso de encontrarse en la mitad superior de los límites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= node->position.y)
		{
			//Si no esta dividida, creamos el sub-árbol que contendrá dicho nodo.
			if (topLeft == nullptr)
			{
				Vector2D start = Vector2D(bounds.topLeft.x, bounds.topLeft.y);
				Vector2D end = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Bounds2D size = Bounds2D(start, end);
				topLeft = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-árbol.
			topLeft->Insert(node);
		}
		//En caso de encontrarse en la mitad inferior de los límites.
		else
		{
			//Si no esta dividida, creamos el sub-árbol que contendrá dicho nodo.
			if (botRight == nullptr)
			{
				Vector2D start = Vector2D(bounds.topLeft.x, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Vector2D end = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, bounds.botRight.y);
				Bounds2D size = Bounds2D(start, end);
				botRight = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-árbol.
			botRight->Insert(node);
		}
	}
	//En caso de encontrarse en la mitad derecha de los límites
	else
	{
		//En caso de encontrarse en la mitad superior de los límites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= node->position.y)
		{
			//Si no esta dividida, creamos el sub-árbol que contendrá dicho nodo.
			if (topRight == nullptr)
			{
				Vector2D start = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, bounds.topLeft.y);
				Vector2D end = Vector2D(bounds.botRight.x, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Bounds2D size = Bounds2D(start, end);
				topRight = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-árbol.
			topRight->Insert(node);
		}
		//En caso de encontrarse en la mitad inferior de los límites.
		else
		{
			//Si no esta dividida, creamos el sub-árbol que contendrá dicho nodo.
			if (botRight == nullptr)
			{
				Vector2D start = Vector2D((bounds.topLeft.x + bounds.botRight.x) / 2, (bounds.topLeft.y + bounds.botRight.y) / 2);
				Vector2D end = Vector2D(bounds.botRight.x, bounds.botRight.y);
				Bounds2D size = Bounds2D(start, end);
				botRight = new Quadtree(size);
			}
			//Insertamos el nodo en el sub-árbol.
			botRight->Insert(node);
		}
	}
}

QTNode* const Quadtree::Search(const Vector2D point)
{
	//Comprobamos que el punto se encuentra dentro de los límites.
	if (!IsInsideBounds(point))
		return nullptr;

	//Si el sub-árbol en el que estamos tiene un nodo asignado
	//y, por lo tanto, no se puede dividir más,
	//devolvemos el nodo asignado a este sub-árbol
	if (node != nullptr)
		return node;

	//Comprobamos si se encuentra en la mitad izquierda de los límites.
	if ((bounds.topLeft.x + bounds.botRight.x) / 2 >= point.x)
	{
		//En caso de encontrarse en la mitad superior de los límites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= point.y)
		{
			//Si no existe un sub-árbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (topLeft == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-árbol.
			return topLeft->Search(point);
		}
		//En caso de encontrarse en la mitad inferior de los límites.
		else
		{
			//Si no existe un sub-árbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (botLeft == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-árbol.
			return botLeft->Search(point);
		}
	}
	else
	{
		//En caso de encontrarse en la mitad superior de los límites.
		if ((bounds.topLeft.y + bounds.botRight.y) / 2 >= point.y)
		{
			//Si no existe un sub-árbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (topRight == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-árbol.
			return topRight->Search(point);
		}
		//En caso de encontrarse en la mitad inferior de los límites.
		else
		{
			//Si no existe un sub-árbol, quiere decir que este nodo no existe, por lo tanto devuelve nullptr.
			if (botRight == nullptr)
				return nullptr;
			//Busca el nodo dentro del sub-árbol.
			return botRight->Search(point);
		}
	}
}
