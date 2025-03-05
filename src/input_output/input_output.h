#ifndef INPUT_OUTPUT_INPUT_OUTPUT_H
#define INPUT_OUTPUT_INPUT_OUTPUT_H

#include "../data_structures/my_vector.h"
#include "../data_structures/my_string.h"
#include "../structs.h"

/**
 * Reads flight information from input and populates the graph
 * @param hash_table Hash table for city name lookups
 * @param graph Graph representation of flight connections
 */
void ReadFlights(int* hash_table, MyVector<MyVector<FieldDistancePair>>& graph);

/**
 * Prints the route information based on query type
 * @param shortest_route Vector containing shortest route information
 * @param city_names Vector of city names
 * @param source_city_index Index of the source city
 * @param destination_city_index Index of the destination city
 * @param query_type If true, prints the full route; otherwise prints only distance
 */
void PrintOutput(MyVector<FieldDijkstra>& shortest_route, MyVector<MyString>& city_names, int source_city_index, int destination_city_index, bool query_type);

/**
 * Reads and processes query requests
 * @param hash_table Hash table for city name lookups
 * @param graph Graph representation of flight connections
 * @param city_names Vector of city names
 */
void ReadQueries(int*& hash_table, MyVector<MyVector<FieldDistancePair>>& graph, MyVector<MyString>& city_names);

#endif // INPUT_OUTPUT_INPUT_OUTPUT_H
