#pragma once
#include "QuadtreeNode.h"
#include <math.h>

class Quadtree
{
	Bounds2D bounds;
	QTNode* node;
	Quadtree* topLeft, *topRight, *botLeft, *botRight;

public:
	Quadtree(const Bounds2D bounds) {
		this->bounds = bounds;
		node = nullptr;
		topLeft = topRight = botLeft = botRight = nullptr;
	}
	~Quadtree() { 
		if (topLeft != nullptr)
			delete topLeft;
		if (botLeft != nullptr) 
			delete botLeft;
		if (topRight != nullptr) 
			delete topRight;
		if (botRight != nullptr)
			delete botRight;
		
		topLeft = nullptr;
		botLeft = nullptr;
		topRight = nullptr;
		botRight = nullptr;

		if (node != nullptr)
			delete node;
		node = nullptr;
	}
	void Insert (QTNode* node);
	QTNode* const Search(const Vector2D point);

private:
	__forceinline const bool IsInsideBounds(const Vector2D position) {
		return (position.x > bounds.topLeft.x&& position.x < bounds.botRight.x && position.y > bounds.topLeft.y&& position.y < bounds.botRight.y);
	}
};

