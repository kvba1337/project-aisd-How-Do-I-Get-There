#include "city.h"
#include "../board/board.h"
#include "../consts.h"
#include <iostream>

using namespace std;

int FindVertexIndexOfCity(const MyVector<char>& board, int index, const BoardDimensions& board_dimensions) {
    const int column_number = index % board_dimensions.w;
    const int row_number = index / board_dimensions.w;

    if (board[index] == '*') {
        return index;
    }

    for (int temp_row_number = row_number - 1; temp_row_number <= row_number + 1; temp_row_number++) {
        for (int temp_column_number = column_number - 1; temp_column_number <= column_number + 1; temp_column_number++) {
            if (IsPositionValid(temp_row_number, temp_column_number, board_dimensions)) {
                const int temp_index = temp_row_number * board_dimensions.w + temp_column_number;
                if (board[temp_index] == '*') {
                    return temp_index;
                }
            }
        }
    }

    return kUndefined;
}

void FindCities(const MyVector<char>& board, const BoardDimensions& board_dimensions, MyVector<City>& cities) {
    City city;
    bool is_reading_city = false;

    for (int i = 0; i < board_dimensions.size; i++) {
        if (IsAlphanumeric(board[i])) {
            if (!is_reading_city) {
                city.name = "";
                city.name += board[i];
                city.vertex_index = FindVertexIndexOfCity(board, i, board_dimensions);
                is_reading_city = true;

                if (i == board_dimensions.size - 1 && city.vertex_index != kUndefined) {
                    cities.PushBack(city);
                }
            }
            else {
                city.name += board[i];
            }
        }
        else if (is_reading_city) {
            if (city.vertex_index == kUndefined) {
                city.vertex_index = FindVertexIndexOfCity(board, i - 1, board_dimensions);
            }

            cities.PushBack(city);

            city.name = "";
            city.vertex_index = kUndefined;
            is_reading_city = false;
        }
    }
}

void FillCityNamesVector(const MyVector<City>& cities, MyVector<MyString>& city_names) {
    for (size_t i = 0; i < cities.size(); i++) {
        city_names[cities[i].vertex_index] = cities[i].name;
    }
}

void FillHashTable(int*& hash_table, const MyVector<City>& cities) {
    for (size_t i = 0; i < cities.size(); i++) {
        hash_table[cities[i].name.Hash()] = cities[i].vertex_index;
    }
}
