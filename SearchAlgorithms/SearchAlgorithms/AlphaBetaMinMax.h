#pragma once

#include <algorithm>
#include <ctime>
#include <cstdlib>

#define AISCORE -1
#define PLAYERSCORE 1

class AlphaBetaMinMax
{
public:
	//Devuelve una pareja de integers.
	//El primer valor equivale a la puntuación asignada al movimiento.
	//El segundo valor equivale a la respuesta que va a devolver dicho movimiento.
	static std::pair<int, int> MinMax(int difficulty, int alpha, int beta, bool AIturn, int currentValue);
};