#pragma once
#include "myString.h"

struct BoardDimensions {
	int w;
	int h;
	int size;
};

struct FieldDistancePair {
	int fieldIndex;
	int neighborFieldDistance;
};

struct City {
	myString name;
	int vertexIndex;
};

struct FieldDijkstra {
	int fieldIndex;
	int distance;
	int previousFieldIndex;
	bool isVisited;
};