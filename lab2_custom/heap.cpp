#include "heap.h"

#include "catch2.hpp"

#include <iostream>

namespace lab02 {
    int heapLeft(int i) {
        return 2 * i;
    }

    int heapRight(int i) {
        return 2 * i + 1;
    }

    void maxHeapify(int *A, int heapsize, int i, Operation *opAsg = nullptr, Operation *opCmp = nullptr) {
        int l = heapLeft(i);
        int r = heapRight(i);
        int largest;

        if (opCmp) opCmp->count(1);
        if (l <= heapsize && A[l - 1] > A[i - 1]) {
            largest = l;
        } else {
            largest = i;
        }

        if (opCmp) opCmp->count(1);
        if (r <= heapsize && A[r - 1] > A[largest - 1]) {
            largest = r;
        }

        if (largest != i) {
            if (opAsg) opAsg->count(3);
            int aux = A[i - 1];
            A[i - 1] = A[largest - 1];
            A[largest - 1] = aux;
            maxHeapify(A, heapsize, largest, opAsg, opCmp);
        }
    }

    void maxHeapifyTopDown(int *A, int heapsize, int i, Operation *opAsg = nullptr, Operation *opCmp = nullptr) {
        int parent = (i - 1) / 2;

        while (i && A[i] > A[parent]) {
            int aux = A[i];
            A[i] = A[parent];
            A[parent] = aux;

            i = parent;
            parent = (i - 1) / 2;
        }
    }

    /**
     * @brief BubbleSort in Iterative form
     *
     * @param values the array to be sorted
     * @param n number of elements in values
     * @param opAsg counter for assignments
     * @param opCmp counter for comparisons
     */
    void iterativeSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        int flag = 1;
        while (flag == 1) {
            flag = 0;
            for (int i = 0; i < n - 1; i++) {
                if (opCmp) opCmp->count(1);
                if (values[i + 1] < values[i]) {
                    if (opAsg) opAsg->count(3);
                    int aux = values[i + 1];
                    values[i + 1] = values[i];
                    values[i] = aux;
                    flag = 1;
                }
            }
        }
    }

    void recursiveSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        // Base case
        if (n == 1) return;

        boolean flag = 0;

        for (int i = 0; i < n - 1; i++) {
            if (opCmp) opCmp->count(1);
            if (values[i] > values[i + 1]) {
                if (opAsg) opAsg->count(3);
                int aux = values[i];
                values[i] = values[i + 1];
                values[i + 1] = aux;
                flag = 1;
            }
        }

        if (flag == 0) return;

        recursiveSort(values, n - 1, opAsg, opCmp);
    }

    void buildHeap_BottomUp(int *values, int n, Operation *opAsg, Operation *opCmp) {
        int heapsize = n;

        for (int i = n / 2; i > 0; i--) {
            maxHeapify(values, heapsize, i, opAsg, opCmp);
        }
    }

    void buildHeap_TopDown(int *values, int n, Operation *opAsg, Operation *opCmp) {
        int heapsize = n;
        for (int i = 1; i < n; i++) {
            maxHeapifyTopDown(values, heapsize, i, opAsg, opCmp);
        }
    }

    void heapSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        buildHeap_BottomUp(values, n, opAsg, opCmp);
        int heapsize = n;

        for (int i = n; i > 1; i--) {
            if (opCmp) opCmp->count(3);
            int aux = values[0];
            values[0] = values[i - 1];
            values[i - 1] = aux;
            heapsize--;
            maxHeapify(values, heapsize, 1, opAsg, opCmp);
        }
    }

    void demonstrate(int size) {
        int data[10];
        FillRandomArray(data, 10, 0, 10, false, UNSORTED);
        buildHeap_TopDown(data, 10);
        for (int i = 0; i < 10; i++) {
            std::cout << data[i] << "\n";
        }
    }

    TEST_CASE("Heap methods") {
        // Use REQUIRE( [condition] ); to perform checks
        // You can use the FillRandomArray to generate input data
        // and the IsSorted method to test the result of your sorting function.
        // For example:
        int data[10];
        FillRandomArray(data, 10);
        iterativeSort(data, 10);
        REQUIRE(IsSorted(data, 10));

        FillRandomArray(data, 10);
        recursiveSort(data, 10);
        REQUIRE(IsSorted(data, 10));

        int maxHeap[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        int maxHeapCorrect[] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
        int n = std::size(maxHeap);
        buildHeap_BottomUp(maxHeap, n);
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (maxHeap[i] != maxHeapCorrect[i]) {
                flag = false;
            }
        }
        REQUIRE(flag == true);

        int heapsortArray[100];
        FillRandomArray(heapsortArray, 100);
        heapSort(heapsortArray, 100);
        REQUIRE(IsSorted(heapsortArray, 100));
    }

    void performance(Profiler &profiler, AnalysisCase whichCase) {
        // TODO: Write your performance analysis here, as explained in the readme
        std::cout << "Performnce...\n\n";


        // You should use profiler.createOperation to pass the counter to each sorting function
    }

    void benchmark(Profiler &profiler, AnalysisCase whichCase) {
        // TODO: Write your benchmarks here, as explained in the readme
        // You should use profiler.startTimer/stopTimer for measuring and plotting measured time
        std::cout << "Setting world records...\n\n";
        for (int n = 100; n <= 10000; n+=100) {
            int valuesIter[n];
            int valuesRec[n];
            int valuesHeapsort[n];
            FillRandomArray(valuesIter, n);
            memcpy(valuesRec, valuesIter, n * sizeof(int));
            memcpy(valuesHeapsort, valuesIter, n * sizeof(int));

            std::cout << "Iterative Sort... ";

            profiler.startTimer("bubble_iterative", n);
            iterativeSort(valuesIter, n);
            profiler.stopTimer("bubble_iterative", n);

            std::cout << "DONE\n\n";

            std::cout << "Recursive sort... ";

            profiler.startTimer("bubble_recursive", n);
            recursiveSort(valuesIter, n);
            profiler.stopTimer("bubble_recursive", n);

            std::cout << "DONE\n\n";

            std::cout << "Heapsort... ";

            profiler.startTimer("heapsort", n);
            heapSort(valuesIter, n);
            profiler.stopTimer("heapsort", n);

            std::cout << "DONE\n\n";

        }

        profiler.createGroup("sorting_algorithms", "bubble_iterative", "bubble_recursive", "heapsort");
        profiler.createGroup("recursive_and_heapsort", "heapsort", "bubble_recursive");
        std::cout << "Showing graphs...";
    }
} // namespace lab02
