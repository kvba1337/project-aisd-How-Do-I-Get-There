#include "graph.h"
#include "../board/board.h"
#include "../consts.h"
#include <iostream>

using namespace std;

namespace {
    constexpr int kDirectionCount = 4;
    constexpr int kColumnDirections[kDirectionCount] = { 0, -1, 0, 1 };
    constexpr int kRowDirections[kDirectionCount] = { -1, 0, 1, 0 };

    constexpr char kCityField = '#';
    constexpr char kRoadField = '*';
}

void ConvertMapToGraph(MyVector<char>& board, BoardDimensions board_dimensions, MyVector<MyVector<FieldDistancePair>>& graph) {
    for (int current_index = 0; current_index < board_dimensions.size; current_index++) {
        if (board[current_index] != kCityField && board[current_index] != kRoadField) {
            continue;
        }

        int column_number = current_index % board_dimensions.w;
        int row_number = current_index / board_dimensions.w;

        for (int direction_index = 0; direction_index < kDirectionCount; direction_index++) {
            int neighbor_row = row_number + kRowDirections[direction_index];
            int neighbor_column = column_number + kColumnDirections[direction_index];

            if (!IsPositionValid(neighbor_row, neighbor_column, board_dimensions)) {
                continue;
            }

            int neighbor_index = neighbor_row * board_dimensions.w + neighbor_column;

            if (board[neighbor_index] == kCityField || board[neighbor_index] == kRoadField) {
                graph[current_index].PushBack({ neighbor_index, kDefaultDistance });
            }
        }
    }
}
