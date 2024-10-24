#include "quick_sort.h"

#include "catch2.hpp"

#include <iostream>
#include <set>

namespace lab03 {
    /**
     * this is the 0-indexed version
     * @param i index inside heap
     * @return parent of heap element with index i
     */
    int parent(int i) {
        return (i -1)/ 2;
    }

    /**
     * this is the 0-indexed version
     * @param i index inside heap
     * @return left child of ith element in heap
     */
    int left(int i) {
        return 2 * i + 1;
    }

    /**
     * this is the 0-indexed version
     * @param i index inside heap
     * @return right child of ith element in heap
     */
    int right(int i) {
        return 2 * i + 2;
    }

    /**
     * Maintains the heap-property. Recursive
     * @param A heap
     * @param i heap index
     */
    void maxHeapify(int* A, int heapsize, int i, Operation* opAsg = nullptr, Operation* opCmp = nullptr) {
        int l = left(i);
        int r = right(i);
        int largest;

        if (opCmp) opCmp->count(1);
        if (l < heapsize && A[l] > A[i]) {
            largest = l;
        } else {
            largest = i;
        }

        if (opCmp) opCmp->count(1);
        if (r < heapsize && A[r] > A[largest]) {
            largest = r;
        }

        if (largest != i) {
            if (opAsg) opAsg->count(3);
            std::swap(A[i], A[largest]);
            maxHeapify(A, heapsize, largest);
        }
    }

    void buildMaxHeap(int* A, int n, Operation* opAsg = nullptr, Operation* opCmp = nullptr) {
        int heapsize = n;

        for (int i = n/2; i >= 0; i--) {
            maxHeapify(A, heapsize, i);
        }
    }

    void heapsort(int* A,int n) {
        buildMaxHeap(A, n);
        int heapsize = n;

        for (int i = n-1; i > 0; i--) {
            std::swap(A[0], A[i]);
            heapsize--;
            maxHeapify(A, heapsize, 0);
        }
    }

    void quickSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        // TODO: Quick sort implementation here
    }

    void hybridizedQuickSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        // TODO: Hybridized quick sort implementation here
    }

    void quickSelect(int *values, int n, Operation *opAsg, Operation *opCmp) {
        // TODO: Quick select implementation here
    }

    void demonstrate(int size) {
        // TODO: Write a small demo for each sorting method here
        int n = 10;
        int A[n] = {12, 23, 14, 10, 7, 19, 20, 8, 6, 13};
        int A_heap[n];
        int A_heapsort[n];
        memcpy(A_heap, A, n*sizeof(int));
        memcpy(A_heapsort, A, n*sizeof(int));

        std::cout << "Initial array: ";
        for (int i = 0; i < n; i++) {
            std::cout << A[i] << " ";
        }

        std::cout << "\n";
        std::cout << "Max Heapified: ";
        buildMaxHeap(A_heap, n);

        for (int i = 0; i < n; i++) {
            std::cout << A_heap[i] << " ";
        }

        std::cout << "\n";

        std::cout << "Heapsort: ";
        heapsort(A_heapsort, n);

        for (int i = 0; i < n; i++) {
            std::cout << A_heapsort[i] << " ";
        }

        std::cout << "\n";
    }

    TEST_CASE("Quick sort") {
        // TODO: Write your unit tests here
        // Use REQUIRE( [condition] ); to perform checks
        // You can use the FillRandomArray to generate input data
        // and the IsSorted method to test the result of your sorting function.
        // For example:
        //   int data[100];
        //   FillRandomArray(data, 100);
        //   bubbleSort(data, 100);
        //   REQUIRE( IsSorted(data, 100) );
    }

    void performance(Profiler &profiler, AnalysisCase whichCase) {
        // TODO: Write your performance analysis here, as explained in the readme
        // You should use profiler.createOperation to pass the counter to each sorting function
    }

    void benchmark(Profiler &profiler, AnalysisCase whichCase) {
        // TODO: Write your benchmarks here, as explained in the readme
        // You should use profiler.startTimer/stopTimer for measuring and plotting measured time
    }
} // namespace lab03
