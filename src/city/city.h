#ifndef CITY_CITY_H
#define CITY_CITY_H

#include "../data_structures/my_vector.h"
#include "../data_structures/my_string.h"
#include "../structs.h"

/**
 * Find the vertex index associated with a city at the given board index
 * @param board The game board
 * @param index Position on the board to search around
 * @param board_dimensions Dimensions of the game board
 * @return The vertex index of the city, or kUndefined if not found
 */
int FindVertexIndexOfCity(const MyVector<char>& board, int index, const BoardDimensions& board_dimensions);

/**
 * Identify all cities on the board and collect their information
 * @param board The game board
 * @param board_dimensions Dimensions of the game board
 * @param cities Vector to store found cities
 */
void FindCities(const MyVector<char>& board, const BoardDimensions& board_dimensions, MyVector<City>& cities);

/**
 * Fill a vector with city names indexed by their vertex indices
 * @param cities Vector of city information
 * @param city_names Vector to store city names by vertex index
 */
void FillCityNamesVector(const MyVector<City>& cities, MyVector<MyString>& city_names);

/**
 * Fill a hash table mapping city name hashes to vertex indices
 * @param hash_table Hash table to fill
 * @param cities Vector of city information
 */
void FillHashTable(int*& hash_table, const MyVector<City>& cities);

#endif // CITY_CITY_H
