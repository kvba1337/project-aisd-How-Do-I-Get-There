#pragma once
#include "myString.h"
#include "myVector.h"
#include "structs.h"
#include "consts.h"
#include "priorityQueue.h"

// main functions


// reads in board
void readBoard(myVector<char>& board, BoardDimensions& board_dimensions);

// reads in cities from the board
void findCities(const myVector<char>& board, BoardDimensions board_dimensions, myVector<City>& cities);

// converts map to graph
void convertMapToGraph(myVector<char>& board, BoardDimensions board_dimensions, myVector<myVector<FieldDistancePair>>& graph);

// fills vector with city names
void fillCityNamesVector(myVector<City> cities, myVector<myString>& cityNames);

// fills hash table with hashed names of cities and their indexes
void fillHashTable(int*& hash_table, myVector<City> cities);

// reads in flight connections
void readFlights(int* hash_table, myVector<myVector<FieldDistancePair>>& graph);

// reads in queries
void readQueries(int*& hash_table, myVector<myVector<FieldDistancePair>>& graph, myVector<myString>& cityNames);


// additional functions


// checks if a character is a letter or digit
bool isAlphanumeric(char c);

// checks if a position is within the board
bool isPositionValid(int rowNumber, int columnNumber, BoardDimensions board_dimensions);

// finds a vertex index of a city
int findVertexIndexOfCity(const myVector<char>& board, int index, BoardDimensions board_dimensions);

// finds shortest route between sourceCityIndex and rest of the fields
void dijkstraSearch(myVector<myVector<FieldDistancePair>>& graph, myVector<FieldDijkstra>& shortestRoute, int sourceCityIndex);

// finds the route indexes between sourceCityIndex and destinationCityIndex
myVector<int> findRouteIndexes(myVector<FieldDijkstra>& shortestRoute, myVector<int>& routeIndexes, int sourceCityIndex, int destinationCityIndex);

// prints output
void printOutput(myVector<FieldDijkstra>& shortestRoute, myVector<myString>& cityNames, int sourceCityIndex, int destinationCityIndex, bool queryType);