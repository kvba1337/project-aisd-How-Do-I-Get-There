#include "board.h"
#include <iostream>

using namespace std;

void ReadBoard(MyVector<char>& board, BoardDimensions& board_dimensions) {
    cin >> board_dimensions.w >> board_dimensions.h;

    board_dimensions.size = board_dimensions.w * board_dimensions.h;

    board.Reserve(board_dimensions.size);

    char input;
    for (int i = 0; i < board_dimensions.size; i++) {
        cin >> input;
        board.PushBack(input);
    }
}

bool IsAlphanumeric(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}

bool IsPositionValid(int row_number, int column_number, const BoardDimensions& board_dimensions) {
    return row_number >= 0 &&
           row_number < board_dimensions.h &&
           column_number >= 0 &&
           column_number < board_dimensions.w;
}
