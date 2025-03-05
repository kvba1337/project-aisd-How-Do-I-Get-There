#include "dijkstra.h"
#include "../data_structures/priority_queue.h"
#include "../consts.h"
#include <iostream>
#include <climits>

using namespace std;

void DijkstraSearch(const MyVector<MyVector<FieldDistancePair>>& graph,
                   MyVector<FieldDijkstra>& shortest_route,
                   int source_city_index) {
    for (size_t i = 0; i < shortest_route.size(); i++) {
        shortest_route[i].field_index = kUndefined;
        shortest_route[i].distance = INT_MAX;
        shortest_route[i].previous_field_index = kUndefined;
        shortest_route[i].is_visited = false;
    }

    shortest_route[source_city_index].distance = kInitialDistance;

    PriorityQueue priority_queue;
    priority_queue.Push({ source_city_index, kInitialDistance });

    while (!priority_queue.IsEmpty()) {
        int current_field_index = priority_queue.Top().field_index;
        priority_queue.Pop();

        if (shortest_route[current_field_index].is_visited) {
            continue;
        }

        shortest_route[current_field_index].is_visited = true;

        for (size_t i = 0; i < graph[current_field_index].size(); i++) {
            int neighbor_index = graph[current_field_index][i].field_index;
            int edge_distance = graph[current_field_index][i].neighbor_field_distance;
            int total_distance = shortest_route[current_field_index].distance + edge_distance;

            if (total_distance < shortest_route[neighbor_index].distance) {
                shortest_route[neighbor_index].field_index = neighbor_index;
                shortest_route[neighbor_index].distance = total_distance;
                shortest_route[neighbor_index].previous_field_index = current_field_index;
                priority_queue.Push({ neighbor_index, total_distance });
            }
        }
    }
}

MyVector<int>& FindRouteIndexes(const MyVector<FieldDijkstra>& shortest_route,
                              MyVector<int>& route_indexes,
                              int source_city_index,
                              int destination_city_index) {
    int current_field_index = destination_city_index;

    while (current_field_index != source_city_index) {
        route_indexes.PushBack(current_field_index);
        current_field_index = shortest_route[current_field_index].previous_field_index;
    }

    return route_indexes;
}
