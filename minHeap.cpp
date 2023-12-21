/*
 * Eric Vien
 * 2120
 * 11/25/2023
 */

#include "minHeap.h"
#include <iostream>

void minHeap::siftUp(int pos) {
    int tempVal = heap[pos];

    while (pos > 0 && tempVal < heap[(pos - 1) / 2]) {
        heap[pos] = heap[(pos - 1) / 2];

        pos = (pos - 1) / 2;
    }

    heap[pos] = tempVal;
}

void minHeap::siftDown(int pos) {
    int tempVal = heap[pos];
    int heapSize = heap.size();

    while ((2 * pos) + 1 < heapSize) {
        int child = (2 * pos) + 1;

        if (child + 1 < heapSize && heap[child + 1] < heap[child]) {
            child++;
        }
        if (tempVal <= heap[child]) break;

        heap[pos] = heap[child];
        pos = child;
    }

    heap[pos] = tempVal;
}

minHeap::minHeap(vector<int> data) {
    heap = data;
    int heapSize = heap.size();

    for (int e = (heapSize - 2) / 2; e >= 0; e--) {
        siftDown(e);
    }
}

void minHeap::insert(int value) {
    heap.push_back(value);

    siftUp(heap.size() - 1);
}

int minHeap::removeMin() {
    int minValue = heap[0];

    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        siftDown(0);
    }

    return minValue;
}


int main() {
    return 0;
}

