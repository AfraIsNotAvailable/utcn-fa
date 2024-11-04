#include "quick_sort.h"

#include <deque>

#include "catch2.hpp"

#include <iostream>

using namespace std;

/*
 * In mod normal Quicksort este mai rapid ca Heapsort
 * Dar, la heapsort -> WORST: O(nlogn)
 *      la quicksort-> WORST: O(n^2)
 *
 * De aceea exista Quicksort Hibridizat sau Introsort care schimba metoda de
 * sortare cand gaseste un caz DEFAVORABIL pentru Quicksort
 *
 * In caz MEDIU STATISTIC Quicksort este mai rapid, desi graficele de operatii
 * ale celor doi algoritmi de sortare sunt apropiate si liniare
 *
 */

namespace lab03 {
    /**
     * this is the 0-indexed version
     * @param i index inside heap
     * @return parent of heap element with index i
     */
    int parent(int i) {
        return (i - 1) / 2;
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
    void maxHeapify(int *A, int heapsize, int i, Operation *opAsg = nullptr, Operation *opCmp = nullptr) {
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
            maxHeapify(A, heapsize, largest, opAsg, opCmp);
        }
    }

    void buildMaxHeap(int *A, int n, Operation *opAsg = nullptr, Operation *opCmp = nullptr) {
        int heapsize = n;

        for (int i = n / 2; i >= 0; i--) {
            maxHeapify(A, heapsize, i, opAsg, opCmp);
        }
    }

    void heapsort(int *A, int n, Operation *opAsg = nullptr, Operation *opCmp = nullptr) {
        buildMaxHeap(A, n, opAsg, opCmp);
        int heapsize = n;

        for (int i = n - 1; i > 0; i--) {
            if (opAsg) opAsg->count(3);
            swap(A[0], A[i]);
            heapsize--;
            maxHeapify(A, heapsize, 0, opAsg, opCmp);
        }
    }

    int partition(int *values, int low, int high, Operation *opAsg = nullptr, Operation *opCmp = nullptr) {
        int pivot = values[high];
        if (opAsg) opAsg->count(1);
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (opCmp) opCmp->count(1);
            if (values[j] < pivot) {
                i++;
                swap(values[i], values[j]);
                if (opAsg) opAsg->count(3);
            }
        }
        swap(values[i + 1], values[high]);
        if (opAsg) opAsg->count(3);
        return i + 1;
    }

    void quickSort(int *values, int low, int high, Operation *opAsg, Operation *opCmp) {
        if (low < high) {
            int pivot = partition(values, low, high, opAsg, opCmp);
            quickSort(values, low, pivot - 1, opAsg, opCmp);
            quickSort(values, pivot + 1, high, opAsg, opCmp);
        }
    }

    /**
     * @brief Binary Search implementation
     */
    void insertionSort(int *values, int n, Operation *opAsg = nullptr, Operation *opCmp = nullptr) {
        for (int i = 1; i < n; i++) {
            const int aux = values[i];
            int left = 0;
            int right = i;

            while (left < right) {
                const int mid = left + (right - left) / 2;
                if (opCmp) opCmp->count(1);
                if (values[mid] < values[i]) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            int p = i;
            while (p > left) {
                if (opAsg) opAsg->count(1);
                values[p] = values[p - 1];
                p--;
            }
            if (opAsg) opAsg->count(1);
            values[left] = aux;
        }
    }

    void hybridizedQuickSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        if (n <= 30) {
            insertionSort(values, n, opAsg, opCmp);
        } else {
            quickSort(values, 0, n - 1, opAsg, opCmp);
        }
    }

    void quickSelect(int *values, int low, int high, int sel, Operation *opAsg, Operation *opCmp) {
        // TODO: Quick select implementation here
    }

    void demonstrate(int sizeArr) {
        const char *sInitial = "Initial array";
        const char *sHeapified = "Max Heapified";
        const char *sHeapsorted = "Heapsort-ed";
        const char *sQuicksorted = "Quicksort-ed";
        const char *sHybridized = "Hybridiz-ed";

        int rangeMin = 10;
        int rangeMax = 50000;

        int arr[sizeArr];
        FillRandomArray(arr, sizeArr, rangeMin, rangeMax, false, UNSORTED);

        int arrHeap[sizeArr];
        int arrHeapsort[sizeArr];
        int arrQuicksort[sizeArr];
        int arrHybridsort[sizeArr];

        CopyArray(arrHeap, arr, sizeArr);
        CopyArray(arrHeapsort, arr, sizeArr);
        CopyArray(arrQuicksort, arr, sizeArr);
        CopyArray(arrHybridsort, arr, sizeArr);

        printf("\b%*s: ", -16, sInitial);
        for (int i = 0; i < sizeArr; i++) {
            printf("%d ", arr[i]);
        }

        printf("\n%*s: ", -16, sHeapified);
        buildMaxHeap(arrHeap, sizeArr);

        for (int i = 0; i < sizeArr; i++) {
            printf("%d ", arrHeap[i]);
        }

        printf("\n%*s: ", -16, sHeapsorted);

        heapsort(arrHeapsort, sizeArr);

        for (int i = 0; i < sizeArr; i++) {
            printf("%d ", arrHeapsort[i]);
        }

        printf("\n%*s: ", -16, sQuicksorted);

        quickSort(arrQuicksort, 0, sizeArr - 1);

        for (int i = 0; i < sizeArr; i++) {
            printf("%d ", arrQuicksort[i]);
        }

        printf("\n%*s: ", -16, sHybridized);

        hybridizedQuickSort(arrHybridsort, sizeArr);

        for (int i = 0; i < sizeArr; i++) {
            printf("%d ", arrHybridsort[i]);
        }

        printf("\n");
    }

    TEST_CASE("Quick sort") {
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
        // You should use profiler.createOperation to pass the counter to each sorting function

        const int REPETITIONS = 5;

        if (whichCase == AVERAGE) {
            for (int i = 0; i < REPETITIONS; i++) {
                for (int sizeArr = 100; sizeArr <= 100000; sizeArr += 100) {
                    printf("Starting sort for %d elements\n", sizeArr);

                    auto opAsgQuicksort = profiler.createOperation("quicksort_asg", sizeArr);
                    auto opCmpQuicksort = profiler.createOperation("quicksort_cmp", sizeArr);
                    auto opAsgHeapsort = profiler.createOperation("heapsort_asg", sizeArr);
                    auto opCmpHeapsort = profiler.createOperation("heapsort_cmp", sizeArr);
                    auto opAsgHybridQuick = profiler.createOperation("hybrid_asg", sizeArr);
                    auto opCmpHybridQuick = profiler.createOperation("hybrid_cmp", sizeArr);
                    printf("Operations created\n");

                    int arrQuicksort[sizeArr];
                    int arrHeapsort[sizeArr];
                    int arrHybrid[sizeArr];
                    FillRandomArray(arrQuicksort, sizeArr);
                    CopyArray(arrHeapsort, arrQuicksort, sizeArr);
                    CopyArray(arrHybrid, arrQuicksort, sizeArr);
                    printf("Arrays filled\n");

                    printf("Quicksort...");
                    quickSort(arrQuicksort, 0, sizeArr - 1, &opAsgQuicksort, &opCmpQuicksort);
                    printf(" done\n");
                    printf("Heapsort...");
                    heapsort(arrHeapsort, sizeArr, &opAsgHeapsort, &opCmpHeapsort);
                    printf(" done\n");
                    printf("Hybridsort...");
                    hybridizedQuickSort(arrHybrid, sizeArr, &opAsgHybridQuick, &opCmpHybridQuick);
                    printf(" done\n");
                }
            }
        } else if (whichCase == WORST) {
            for (int sizeArr = 100; sizeArr <= 100000; sizeArr += 100) {
                printf("Starting sort for %d elements\n", sizeArr);

                auto opAsgQuicksort = profiler.createOperation("quicksort_asg", sizeArr);
                auto opCmpQuicksort = profiler.createOperation("quicksort_cmp", sizeArr);
                auto opAsgHeapsort = profiler.createOperation("heapsort_asg", sizeArr);
                auto opCmpHeapsort = profiler.createOperation("heapsort_cmp", sizeArr);
                auto opAsgHybridQuick = profiler.createOperation("hybrid_asg", sizeArr);
                auto opCmpHybridQuick = profiler.createOperation("hybrid_cmp", sizeArr);
                printf("Operations created\n");

                int arrQuicksort[sizeArr];
                int arrHeapsort[sizeArr];
                int arrHybrid[sizeArr];
                FillRandomArray(arrQuicksort, sizeArr, 10, 50000, false, DESCENDING);
                CopyArray(arrHeapsort, arrQuicksort, sizeArr);
                CopyArray(arrHybrid, arrQuicksort, sizeArr);
                printf("Arrays filled\n");

                printf("Quicksort...");
                quickSort(arrQuicksort, 0, sizeArr - 1, &opAsgQuicksort, &opCmpQuicksort);
                printf(" done\n");
                printf("Heapsort...");
                heapsort(arrHeapsort, sizeArr, &opAsgHeapsort, &opCmpHeapsort);
                printf(" done\n");
                printf("Hybridsort...");
                hybridizedQuickSort(arrHybrid, sizeArr, &opAsgHybridQuick, &opCmpHybridQuick);
                printf(" done\n");
            }
        } else {
            for (int sizeArr = 100; sizeArr <= 100000; sizeArr += 100) {
                printf("Starting sort for %d elements\n", sizeArr);
                auto opAsgQuicksort = profiler.createOperation("quicksort_asg", sizeArr);
                auto opCmpQuicksort = profiler.createOperation("quicksort_cmp", sizeArr);
                auto opAsgHeapsort = profiler.createOperation("heapsort_asg", sizeArr);
                auto opCmpHeapsort = profiler.createOperation("heapsort_cmp", sizeArr);
                auto opAsgHybridQuick = profiler.createOperation("hybrid_asg", sizeArr);
                auto opCmpHybridQuick = profiler.createOperation("hybrid_cmp", sizeArr);
                printf("Operations created\n");

                int arrQuicksort[sizeArr];
                int arrHeapsort[sizeArr];
                int arrHybrid[sizeArr];
                FillRandomArray(arrQuicksort, sizeArr, 10, 50000, false, UNSORTED);
                CopyArray(arrHeapsort, arrQuicksort, sizeArr);
                CopyArray(arrHybrid, arrQuicksort, sizeArr);
                printf("Arrays filled\n");

                printf("Quicksort...");
                quickSort(arrQuicksort, 0, sizeArr - 1, &opAsgQuicksort, &opCmpQuicksort);
                printf(" done\n");
                printf("Heapsort...");
                heapsort(arrHeapsort, sizeArr, &opAsgHeapsort, &opCmpHeapsort);
                printf(" done\n");
                printf("Hybridsort...");
                hybridizedQuickSort(arrHybrid, sizeArr, &opAsgHybridQuick, &opCmpHybridQuick);
                printf(" done\n");
            }
        }

        profiler.addSeries("quicksort_ops", "quicksort_asg", "quicksort_cmp");
        profiler.addSeries("heapsort_ops", "heapsort_asg", "heapsort_cmp");
        profiler.addSeries("hybrid_ops", "hybrid_asg", "hybrid_cmp");

        if (whichCase == AVERAGE) {
            profiler.divideValues("quicksort_ops", REPETITIONS);
            profiler.divideValues("heapsort_ops", REPETITIONS);
            profiler.divideValues("hybrid_ops", REPETITIONS);
            profiler.createGroup("Heapsort Quick AVERAGE", "quicksort_ops", "heapsort_ops");
            profiler.createGroup("Hybrid Quick AVERAGE", "quicksort_ops", "hybrid_ops");
        } else if (whichCase == BEST) {
            profiler.createGroup("Heapsort Quick BEST", "quicksort_ops", "heapsort_ops");
            profiler.createGroup("Hybrid Quick BEST", "quicksort_ops", "hybrid_ops");
        } else {
            profiler.createGroup("Heapsort Quick WORST", "quicksort_ops", "heapsort_ops");
            profiler.createGroup("Hybrid Quick WORST", "quicksort_ops", "hybrid_ops");
        }
    }

    void benchmark(Profiler &profiler, AnalysisCase whichCase) {
        // You should use profiler.startTimer/stopTimer for measuring and plotting measured time

        for (int sizeArr = 100; sizeArr <= 50000; sizeArr += 100) {
            printf("%d\n", sizeArr);
            const int rangeMin = 10;
            const int rangeMax = 50000;


            int arrQuick[sizeArr];
            int arrHybrid[sizeArr];
            if (whichCase == AVERAGE) {
                FillRandomArray(arrQuick, sizeArr);
                CopyArray(arrHybrid, arrQuick, sizeArr);
            } else if (whichCase == WORST) {
                FillRandomArray(arrQuick, sizeArr, rangeMin, rangeMax, false, DESCENDING);
                CopyArray(arrHybrid, arrQuick, sizeArr);
            } else {
                FillRandomArray(arrQuick, sizeArr, rangeMin, rangeMax, false, ASCENDING);
                CopyArray(arrHybrid, arrQuick, sizeArr);
            }

            profiler.startTimer("time_quick", sizeArr);
            quickSort(arrQuick, 0, sizeArr - 1);
            profiler.stopTimer("time_quick", sizeArr);

            profiler.startTimer("time_hybrid", sizeArr);
            hybridizedQuickSort(arrHybrid, sizeArr);
            profiler.stopTimer("time_hybrid", sizeArr);
        }

        if (whichCase == AVERAGE) {
            profiler.createGroup("Time AVERAGE", "time_quick", "time_hybrid");
        } else if (whichCase == WORST) {
            profiler.createGroup("Time WORST", "time_quick", "time_hybrid");
        } else {
            profiler.createGroup("Time BEST", "time_quick", "time_hybrid");
        }
    }
} // namespace lab03
