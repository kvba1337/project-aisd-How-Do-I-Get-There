#include "priorityQueue.h"

void PriorityQueue::heapify_up(int index) {
	int parentIndex = (index - 1) / 2;

	// loop while the current node is smaller than its parent and current node is not the root
	while (index > 0 && heap[index].neighborFieldDistance < heap[parentIndex].neighborFieldDistance) {
		FieldDistancePair tmp = heap[index];
		heap[index] = heap[parentIndex];
		heap[parentIndex] = tmp;

		index = parentIndex;
		parentIndex = (index - 1) / 2;
	}
}

void PriorityQueue::heapify_down(int index) {
	int leftIndex = 2 * index + 1;
	int rightIndex = 2 * index + 2;
	int smallestIndex = index;

	// check if the left child is smaller than the smallest index
	if (leftIndex < (int)heap.size() && heap[leftIndex].neighborFieldDistance < heap[smallestIndex].neighborFieldDistance) {
		smallestIndex = leftIndex;
	}

	// check if the right child is smaller than the smallest index
	if (rightIndex < (int)heap.size() && heap[rightIndex].neighborFieldDistance < heap[smallestIndex].neighborFieldDistance) {
		smallestIndex = rightIndex;
	}

	// if the smallest index is not the current index, swap the elements and heapify down the smallest index
	if (smallestIndex != index) {
		FieldDistancePair tmp = heap[index];
		heap[index] = heap[smallestIndex];
		heap[smallestIndex] = tmp;
		heapify_down(smallestIndex);
	}
}

bool PriorityQueue::isEmpty() const {
	return heap.isEmpty();
}

void PriorityQueue::push(const FieldDistancePair& value) {
	heap.push_back(value);
	heapify_up(heap.size() - 1);
}

void PriorityQueue::pop() {
	if (heap.isEmpty()) {
		return;
	}

	heap[0] = heap[heap.size() - 1];
	heap.pop_back();
	heapify_down(0);
}

FieldDistancePair PriorityQueue::top() const {
	return heap[0];
}