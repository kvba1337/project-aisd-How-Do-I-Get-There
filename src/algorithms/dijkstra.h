#ifndef ALGORITHMS_DIJKSTRA_H
#define ALGORITHMS_DIJKSTRA_H

#include "../data_structures/my_vector.h"
#include "../structs.h"

/**
 * Performs Dijkstra's algorithm to find shortest paths from a source node
 * @param graph The adjacency list representation of the graph
 * @param shortest_route Vector to store the results of Dijkstra's algorithm
 * @param source_city_index The index of the source node
 */
void DijkstraSearch(const MyVector<MyVector<FieldDistancePair>>& graph,
                   MyVector<FieldDijkstra>& shortest_route,
                   int source_city_index);

/**
 * Reconstructs the path from source to destination using the Dijkstra results
 * @param shortest_route The result of Dijkstra's algorithm
 * @param route_indexes Vector to store the path indices
 * @param source_city_index The index of the source node
 * @param destination_city_index The index of the destination node
 * @return The vector containing the path indices
 */
MyVector<int>& FindRouteIndexes(const MyVector<FieldDijkstra>& shortest_route,
                              MyVector<int>& route_indexes,
                              int source_city_index,
                              int destination_city_index);

#endif // ALGORITHMS_DIJKSTRA_H
