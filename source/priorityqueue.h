#pragma once
#include "structs.h"
#include "myVector.h"

class PriorityQueue {
private:
	myVector<FieldDistancePair> heap;

	// moves an element up the heap 
	void heapify_up(int index);

	// moves an element down the heap 
	void heapify_down(int index);

public:
	// returns true if the priority queue is empty and false otherwise
	bool isEmpty() const;

	// adds a new element to the priority queue
	void push(const FieldDistancePair& value);

	// removes the minimum element from the priority queue
	void pop();

	// returns the minimum element in the priority queue 
	FieldDistancePair top() const;
};