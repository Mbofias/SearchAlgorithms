#pragma once

//Un punto en un plano 2D.
struct Vector2D {
	int x, y;

	Vector2D(const int x, const int y) {
		this->x = x;
		this->y = y;
	}

	Vector2D() {
		x = y = 0;
	}
};

//Límites establecidos de un plano 2D.
struct Bounds2D {
	Vector2D topLeft, botRight;

	Bounds2D(const Vector2D topLeft, const Vector2D botRight) {
		this->topLeft = topLeft;
		this->botRight = botRight;
	}

	Bounds2D() {
		topLeft = botRight = Vector2D();
	}
};

//Nodo que contiene un punto almacenado en un Quadtree
struct QTNode {
	Vector2D position;
	char sprite;

	QTNode(Vector2D position, char sprite) {
		this->position = position;
		this->sprite = sprite;
	}

	~QTNode() { }
};