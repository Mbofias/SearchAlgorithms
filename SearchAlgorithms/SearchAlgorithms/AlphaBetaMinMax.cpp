#include "AlphaBetaMinMax.h"

std::pair<int, int> AlphaBetaMinMax::MinMax(int difficulty, int alpha, int beta, bool AIturn, int currentValue)
{
	//Por defecto se le asigna la respuesta '1' y el valor m�ximo o m�nimo dependiendo del "jugador" actual.
	int highScore = AIturn ? AISCORE : PLAYERSCORE;
	int answer = 1;
	//En caso de haber llegado a una puntuaci�n de 10 se devuelven la respuesta y el valor por defecto.
	if (currentValue >= 10)
		return std::make_pair(highScore, answer);

	//Se comprueban todas las respuestas posibles (1-3)
	for (int index = 1; index <= 3; index++)
	{
		int tmpCurrentValue = currentValue + index;

		//Si se trata de el turno de la IA, se maximiza el valor alfa.
		if (AIturn)
		{
			//Se guarda el valor de la puntuaci�n, depender� de los pr�ximos movimientos del �rbol.
			int score = MinMax(difficulty + 1, alpha, beta, false, tmpCurrentValue).first;

			//En caso de tener un movimiento que tenga una mejor puntuaci�n que la puntuaci�n por defecto
			if (highScore < score && tmpCurrentValue < 10)
			{
				//Se modifican la respuesta y valor por defecto, usando los valores actuales.
				highScore = score;
				answer = index;

				//Se guarda en el valor de alpha el valor maximo entre alpha y el valor m�ximo.
				alpha = std::max(alpha, highScore);
				//Si alpha es mayor que beta dejamos de comprobar los nodos siguientes.
				if (beta <= alpha)
					break;
			}

		}
		//Si se trata de el turno del jugador, se minimiza el valor beta.
		else
		{
			int score = MinMax(difficulty + 1, alpha, beta, true, tmpCurrentValue).first;

			if (highScore > score && tmpCurrentValue < 10)
			{
				highScore = score;
				answer = index;

				alpha = std::min(beta, highScore);
				if (beta <= alpha)
					break;
			}

		}
	}

	//Devuelve el valor m�s alto y su respectiva respuesta.
	return std::make_pair(highScore, answer);
}
