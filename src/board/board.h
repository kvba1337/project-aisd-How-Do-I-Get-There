#ifndef BOARD_BOARD_H
#define BOARD_BOARD_H

#include "../data_structures/my_vector.h"
#include "../structs.h"

/**
 * Reads board dimensions and content from standard input
 * @param board Vector to store the board characters
 * @param board_dimensions Structure to store board width, height, and size
 */
void ReadBoard(MyVector<char>& board, BoardDimensions& board_dimensions);

/**
 * Checks if a character is alphanumeric (A-Z, a-z, 0-9)
 * @param c Character to check
 * @return True if the character is alphanumeric, false otherwise
 */
bool IsAlphanumeric(char c);

/**
 * Validates if a position is within the board boundaries
 * @param row_number Row coordinate (0-indexed)
 * @param column_number Column coordinate (0-indexed)
 * @param board_dimensions Board dimensions for boundary checking
 * @return True if the position is valid, false otherwise
 */
bool IsPositionValid(int row_number, int column_number, const BoardDimensions& board_dimensions);

#endif // BOARD_BOARD_H
