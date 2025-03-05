#pragma once
#include "../structs.h"
#include "my_vector.h"
#include <utility>

class PriorityQueue {
private:
    MyVector<FieldDistancePair> heap_;

    void HeapifyUp(int index);
    void HeapifyDown(int index);

public:
    bool IsEmpty() const;
    void Push(const FieldDistancePair& value);
    void Pop();
    FieldDistancePair Top() const;
};
