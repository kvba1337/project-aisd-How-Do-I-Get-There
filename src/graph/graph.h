#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "../data_structures/my_vector.h"
#include "../structs.h"

/**
 * Converts a 2D map representation into a graph structure.
 *
 * @param board The linear representation of the 2D board
 * @param board_dimensions The dimensions of the board
 * @param graph The resulting adjacency list representation of the graph
 */
void ConvertMapToGraph(MyVector<char>& board, BoardDimensions board_dimensions, MyVector<MyVector<FieldDistancePair>>& graph);

#endif // GRAPH_GRAPH_H
