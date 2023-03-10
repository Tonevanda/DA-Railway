// By: Gonçalo Leão
// Based on MutablePriorityQueue.h

#include "Heap.h"

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

Heap::Heap() {
    elems.push_back(0);
	// indices will be used starting in 1
	// to facilitate parent/child calculations
}

Heap::Heap(std::vector<int> v): Heap() {
    // Add the elements to the vector without respecting the heap property
    elems.insert(elems.end(),v.begin(),v.end());

    // Index of the last non-leaf node of vector v
    unsigned int startIdx = v.size() / 2;

    // Move the elements around so that the heap property is respected
    // There is no need to heapify the elements with higher indices since they are leaf nodes
    for(unsigned int i = startIdx; i > 0; i--) {
        heapifyDown(i);
    }
}

bool Heap::empty() {
	return elems.size() == 1;
}

int Heap::extractMin() {
	auto x = elems[1];
    elems[1] = elems.back();
    elems.pop_back();
	if(elems.size() > 1) heapifyDown(1);
	return x;
}

void Heap::insert(int x) {
	elems.push_back(x);
	heapifyUp(elems.size()-1);
}

void Heap::heapifyUp(unsigned int i) {
	auto x = elems[i];
	while (i > 1 && x < elems[parent(i)]) {
        elems[i] = elems[parent(i)];
		i = parent(i);
	}
    elems[i] = x;
}

void Heap::heapifyDown(unsigned int i) {
	auto x = elems[i];
	while (true) {
		unsigned k = leftChild(i);
		if (k >= elems.size())
			break;
		if (k+1 < elems.size() && elems[k+1] < elems[k])
			++k; // right child of i
		if ( ! (elems[k] < x) )
			break;
        elems[i] = elems[k];
		i = k;
	}
    elems[i] = x;
}