#include "Secuencia.h"
#include "Binaria.h"
#include "RBTree.h"
#include "Quadtree.h"
#include "AlphaBetaMinMax.h"

//##################################################
//DESCOMENTAR CUALQUIERA DE LAS DEFINICIONES SIGIUIENTES PARA EJECUTAR EL ALGORITMO EN CUESTIÓN
//##################################################

//#define LINEAR
//#define BINARY
#define RED_BLACK_TREE
//#define QUADTREE
//#define ALPHABETA

//##################################################

int main()
{
#ifdef LINEAR
	//Creamos una lista desordenada
	int listaDesordenada[10]{ 20,15,2,5,9856,34,124,0,534,53 };
	//Llamamos a la función estática 'getElement<>(int, int*, int)' de la clase 'Secuencia'
	//para que recorra la lista entera buscando el objeto seleccionado
	//esta función nos devuelve la posición del objeto en cuestión.
	std::cout << "El elemento se encuentra en la posicion: " << Secuencia::getElement<int>(0, listaDesordenada, sizeof(listaDesordenada) / sizeof(listaDesordenada[0])) << std::endl;
#endif //LINEAR

#ifdef BINARY
	//Creamos una lista ordenada 
	//(TIENEN QUE SER ELEMENTOS CON LOS OPERADORES '<' Y '>' SOBRECARGADOS)
	int listaOrdenada[10]{ 2,4,6,8,10,12,14,16,18,20 };
	//Llamamos a la función estática 'getElement<>(int, int*, int, int)' de la clase 'Binaria'
	//para que vaya dividiendo la lista en secciones y comprobando en que sección está el objeto hasta encontrarlo
	//esta función nos devuelve la posición del objeto en cuestión.
	std::cout << "El elemento se encuentra en la posicion: " << Binaria::getElement<int>(6, listaOrdenada, 0, sizeof(listaOrdenada) / sizeof(listaOrdenada[0]) - 1) << std::endl;
#endif //BINARY

#ifdef RED_BLACK_TREE
	//Creamos un árbol rojo negro.
	RBTree* myTree = new RBTree();

	//#############################################################################################
		////Le añadimos 15 nodos con valores al azar entre 0 y 50.
		//for (int index = 0; index < 15; index++)
		//	myTree->InsertNode(rand() % 51);
		////Imprimimos en la consola la estructura del árbol.
		//myTree->PrintTree();
	//#############################################################################################

	//Realizamos un bucle para permitir añadir nuevos nodos al árbol, y ver como ha quedado ordenado.
	bool keepAdding = true;
	do 
	{
		int value;
		std::cout << "Escribe el valor que desees insertar:";
		std::cin >> value;
		//Insertamos el nodo.
		myTree->InsertNode(value);
		//Imprimimos el árbol.
		myTree->PrintTree();
		std::string keep;
		std::cout << "Quieres seguir jugando? (y/n)";
		std::cin >> keep;
		if (keep == "n")
			keepAdding = false;
	} while (keepAdding);
	//Liberamos la memoria.
	delete myTree;

#endif //RED_BLACK_TREE

#ifdef QUADTREE
	//Creamos el limite superior izquierdo del plano.
	Vector2D myTopLeftBorder = Vector2D(0, 0);
	//Creamos el limite inferior derecho del plano.
	Vector2D myBotRightBorder = Vector2D(10, 10);
	//Creamos el plano usando esos límites.
	Bounds2D myTreeLimits = Bounds2D(myTopLeftBorder, myBotRightBorder);
	//Creamos el Quadtree al que pertenece el plano creado anteriormente.
	Quadtree* myQuadtree = new Quadtree(myTreeLimits);
	//Le asignamos los siguientes puntos al plano.
	myQuadtree->Insert(new QTNode(Vector2D(5, 5), 'X'));
	myQuadtree->Insert(new QTNode(Vector2D(2, 2), 'O'));
	myQuadtree->Insert(new QTNode(Vector2D(8, 8), 'Z'));
	myQuadtree->Insert(new QTNode(Vector2D(12, 12), 'B'));
	myQuadtree->Insert(new QTNode(Vector2D(5, 5), 'M'));
	//Imprimimos por pantalla el valor del nodo que se encuentra en el punto (5,5).
	//std::cout << "El valor del nodo que se encuentra en la posicion (5,5) es: " << myQuadtree->Search(Vector2D(5, 5))->sprite;
	//Liberamos la memoria.
	delete myQuadtree;
#endif //QUADTREE

#ifdef ALPHABETA
	//Iniciamos la "partida" con 0 puntos.
	int totalValue = 0;
	std::cout << "Se trata de un juego por turnos, cada turno se le suma un valor entre 1 y 3 a la puntuacion, para ganar tienes que hacer que tu oponente sea el que llegue a 10 puntos." << std::endl;
	//Elegimos de forma aleatoria quien juega primero.
	bool playerFirst;
	srand(time(0));
	playerFirst = rand() % 2;
	if (playerFirst)
		std::cout << "#-------------------------#" << std::endl << "Empiezas jugando tu, buena suerte." << std::endl << "#-------------------------#" << std::endl;
	else
		std::cout << "#-------------------------#" << std::endl << "Empieza jugando tu oponente, buena suerte." << std::endl << "#-------------------------#" << std::endl;
	//Bucle de juego, se repite mientras la puntuación total este por debajo de 0.
	while (totalValue < 10)
	{
		//Creamos un integer donde guardaremos la "respuesta" que se da en un turno.
		int value;
		//Ejecuta el turno del personaje que toque.
		if (playerFirst)
		{
			do 
			{
				std::cout << "Escribe un numero entre 1 y 3." << std::endl;
				std::cin >> value;
			} while (value <= 0 || value >= 4);
			std::cout << "Has sumado: " << value << " puntos al total" << std::endl;
		}
		else
		{
			value = AlphaBetaMinMax::MinMax(0, PLAYERSCORE, AISCORE, true, totalValue).second;
			std::cout << "El oponente ha sumado: " << value << " puntos al total" << std::endl;
		}
		//Sumamos el valor a la puntuación total.
		totalValue += value;
		//Cambiamos el turno del jugador actual.
		playerFirst = !playerFirst;
		std::cout << "Puntuacion actual: " << totalValue << std::endl << "#-------------------------#" << std::endl;
	}

	if (playerFirst)
		std::cout << "Felicidades, has ganado." << std::endl;
	else
		std::cout << "Has perdido, suerte la proxima vez." << std::endl;
#endif //ALPHABETA
}