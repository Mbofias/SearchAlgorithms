#pragma once
#include <stdexcept>

//La búsqueda binaria nos permite buscar rapidamente en una lista ordenada.
//La función recorre la lista haciendo saltos y comprobando si es el valor correcto o este queda a su derecha o izquierda.
//En este caso, la función devuelve -1 en caso de no encontrar el elemento dentro de la lista.

struct Binaria
{
	//elementToSearch = el objeto que estamos buscando dentro de la lista.
	//listToSearch = lista dentro de la cual buscamos el objeto.
	//firstIndex = numero en el que se empieza a contar.
	//lastIndex = ultimo numero a tener en cuenta.
	template<typename C>
	static int getElement(C elementToSearch, C listToSearch[], int firstIndex, int lastIndex) {
		//Comprueba si el indice inferior es menor al indice superior
		if (firstIndex < lastIndex)
		{
			//Guarda el punto intermedio entre ambos puntos
			int checkPoint = firstIndex + (lastIndex - firstIndex) / 2;

			//En caso de encontrar en esa posición el objeto, devuelve la posición
			if (listToSearch[checkPoint] == elementToSearch)
				return checkPoint;
			//En caso de encontrarse el objeto a la derecha del punto intermedio
			//vuelve a llamar a la función manteniendo el indice superior
			//y convirtiendo el indice inferior en el punto intermedio + 1
			if (listToSearch[checkPoint] < elementToSearch)
				return getElement<C>(elementToSearch, listToSearch, checkPoint + 1, lastIndex);
			//En caso de encontrarse el objeto a la izquierda del punto intermedio
			//vuelve a llamar a la función manteniendo el indice inferior
			//y convirtiendo el indice superior en el punto intermedio - 1
			if (listToSearch[checkPoint] > elementToSearch)
				return getElement<C>(elementToSearch, listToSearch, firstIndex, checkPoint - 1);
		}
		//En caso de no encontrar el objeto devuelve -1
		return -1;
	}
};