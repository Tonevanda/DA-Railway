// By: Gonçalo Leão
// Based on MutablePriorityQueue.h

#ifndef PROJETO_DA_1_HEAP_H
#define PROJETO_DA_1_HEAP_H

#include <vector>

class Heap {
public:
    Heap();
    Heap(std::vector<int> v);
	void insert(int x);
	int extractMin();
	bool empty();
private:
    std::vector<int> elems;
    void heapifyUp(unsigned int i);
    void heapifyDown(unsigned int i);
};

#endif //PROJETO_DA_1_HEAP_H
