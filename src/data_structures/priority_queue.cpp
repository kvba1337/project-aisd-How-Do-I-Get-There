#include "priority_queue.h"

void PriorityQueue::HeapifyUp(int index) {
    int parent_index = (index - 1) / 2;

    while (index > 0 && heap_[index].neighbor_field_distance < heap_[parent_index].neighbor_field_distance) {
        std::swap(heap_[index], heap_[parent_index]);

        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

void PriorityQueue::HeapifyDown(int index) {
    int left_index = 2 * index + 1;
    int right_index = 2 * index + 2;
    int smallest_index = index;

    if (left_index < static_cast<int>(heap_.size()) &&
        heap_[left_index].neighbor_field_distance < heap_[smallest_index].neighbor_field_distance) {
        smallest_index = left_index;
    }

    if (right_index < static_cast<int>(heap_.size()) &&
        heap_[right_index].neighbor_field_distance < heap_[smallest_index].neighbor_field_distance) {
        smallest_index = right_index;
    }

    if (smallest_index != index) {
        std::swap(heap_[index], heap_[smallest_index]);
        HeapifyDown(smallest_index);
    }
}

bool PriorityQueue::IsEmpty() const {
    return heap_.IsEmpty();
}

void PriorityQueue::Push(const FieldDistancePair& value) {
    heap_.PushBack(value);
    HeapifyUp(heap_.size() - 1);
}

void PriorityQueue::Pop() {
    if (heap_.IsEmpty()) {
        return;
    }

    heap_[0] = heap_[heap_.size() - 1];
    heap_.PopBack();
    HeapifyDown(0);
}

FieldDistancePair PriorityQueue::Top() const {
    return heap_[0];
}
