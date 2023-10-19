#include "functions.h"

int main() {
	BoardDimensions board_dimensions;
	myVector<char> board;
	readBoard(board, board_dimensions);

	myVector<City> cities;
	findCities(board, board_dimensions, cities);

	myVector<myVector<FieldDistancePair>> graph(board_dimensions.size);
	convertMapToGraph(board, board_dimensions, graph);

	int maxCityIndex = cities[cities.size() - 1].vertexIndex;
	myVector<myString> cityNames(maxCityIndex + 1);
	fillCityNamesVector(cities, cityNames);

	int* hash_table = new int[HASH_TABLE_SIZE];
	fillHashTable(hash_table, cities);

	readFlights(hash_table, graph);

	readQueries(hash_table, graph, cityNames);

	delete[] hash_table;

	return 0;
}