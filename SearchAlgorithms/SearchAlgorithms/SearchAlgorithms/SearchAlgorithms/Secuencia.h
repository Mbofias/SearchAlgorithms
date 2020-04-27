#pragma once
#include <stdexcept>

//La búsqueda líneal es el método de búsqueda más simple que hay.
//Sirve tanto para listas ordenadas como desordenadas.
//La función recorre la lista buscando la posición que ocupa el elemento seleccionado.
//En este caso, la función devuelve -1 en caso de no encontrar el elemento dentro de la lista.

struct Secuencia
{
	//elementToSearch = el objeto que estamos buscando dentro de la lista.
	//listToSearch = lista dentro de la cual buscamos el objeto.
	//length = tamaño del array en el que buscamos el objeto;
	template<typename C>
	static int getElement(C elementToSearch, C listToSearch[], int length) {
		//Empieza a recorrer el array
		for (int index = 0; index < length; index++)
			//Comprueba si este es el objeto buscado
			if (listToSearch[index] == elementToSearch)
				return index;
		//En caso de no encontrar el objeto devuelve -1
		return -1;
	}
};