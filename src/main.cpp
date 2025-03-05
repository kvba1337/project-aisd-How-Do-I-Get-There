#include <iostream>
#include <climits>
#include <memory>
#include "board/board.h"
#include "city/city.h"
#include "graph/graph.h"
#include "algorithms/dijkstra.h"
#include "input_output/input_output.h"
#include "structs.h"
#include "consts.h"

int main() {
    BoardDimensions board_dimensions;
    MyVector<char> board;
    ReadBoard(board, board_dimensions);

    MyVector<City> cities;
    FindCities(board, board_dimensions, cities);

    MyVector<MyVector<FieldDistancePair>> graph(board_dimensions.size);
    ConvertMapToGraph(board, board_dimensions, graph);

    const int max_city_index = cities[cities.size() - 1].vertex_index;
    MyVector<MyString> city_names(max_city_index + 1);
    FillCityNamesVector(cities, city_names);

    int* hash_table = new int[kHashTableSize];
    FillHashTable(hash_table, cities);

    ReadFlights(hash_table, graph);
    ReadQueries(hash_table, graph, city_names);

    delete[] hash_table;

    return 0;
}
