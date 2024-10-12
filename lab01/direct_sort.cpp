#include "direct_sort.h"

#include "catch2.hpp"

#include <iostream>

/* Analiza algoritmi
 * Bubble Sort:
 *      total operatii: ~2n^2
 *      complexitate: O(n^2) average & worst case
 *                    O(n) best case (depinde de implementare)
 *      ! cel mai costisitor de rulat in majoritatea cazurilor.
 *      ! cel mai incet din punct de vedere al timpului
 *      ! cel mai simplu din pct de vedere al implementarii (comparativ cu Insertion Sort)
 *
 * Insertion Sort:
 *      total operatii: nlogn
 *      complexitate: O(n^2) average & worst case
 *                    O(nlogn) best case
 *      ! dupa Bubble Sort, cel mai greu de rulat algoritm de sortare
 *      ! mai apropiat de timpul de executie si numarul de operatii al Bubble Sort decat cel al Selection Sort
 *      contrar faptului ca implementarea este foarte asemanatoare cu cea a Selection Sort-ului
 *
 * Binary Insertion Sort:
 *      total operatii: 2logn ??
 *      complexitate: O(n^2) average & worst
 *                    O(nlogn) best
 *      ! prin simpla aditie a cautarii binare algoritmul Insertion SOrt devine mult mai rapid, eficient
 *      ! foarte asemanator ca timp de executie si operatii cu Selection Sort
 * Selection Sort:
 *      total operatii: nlogn
 *      complexitate: O(n^2) average & worst
 *                    O(nlogn) best
 *      ! asemanator cu Binary Insertion Sort ca timp si operatii
 *      ! Selection Sort castiga la ATRIBUIRI
 *      ! Binary Insertion Sort castiga la COMPARATII
*/

namespace lab01 {
    void FillSortedArray(int *values, int n) {
        for (int i = 0; i < n; i++) {
            values[i] = i + 1;
        }
    }

    void FillReverseSortedArray(int *values, int n) {
        for (int i = 0; i < n; i++) {
            values[i] = n - i;
        }
    }

    void bubbleSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
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

    void selectionSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        for (int i = 0; i < n - 1; i++) {
            int j = i;
            for (int p = j + 1; p < n; p++) {
                if (opCmp) opCmp->count(1);
                if (values[j] > values[p]) {
                    j = p;
                }
            }
            if (i != j) {
                const int aux = values[i];
                values[i] = values[j];
                values[j] = aux;
                if (opAsg) opAsg->count(3);
            }
        }
    }

    void FillSelectionSortWorstCase(int *values, int n) {
        // ex: for n = 8 -> values: 8 1 2 3 4 5 6 7

        values[0] = n;
        for (int i = 1; i < n; i++) {
            values[i] = i;
        }
    }

    void insertionSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
        for (int i = 1; i <= n; i++) {
            for (int p = 0; p < i; p++) {
                if (opCmp) opCmp->count(1);
                if (values[p] > values[i]) {
                    if (opAsg) opAsg->count(3);
                    const int aux = values[i];
                    values[i] = values[p];
                    values[p] = aux;
                }
            }
        }
    }

    void binaryInsertionSort(int *values, int n, Operation *opAsg, Operation *opCmp) {
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

    void printArray(int *values, int n) {
        for (int i = 0; i < n; i++) {
            std::cout << values[i] << " ";
        }
    }

    void demonstrate(int size) {
        std::cout << "Sorting algorithms demo...\n\n";

        // Demonstratie BubbleSort
        int data[size];
        FillRandomArray(data, size, 10, 100);
        bubbleSort(data, size);
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }

        std::cout << std::endl;

        // Demo SelectionSort
        int data1[size];
        FillRandomArray(data1, size, 10, 100);
        selectionSort(data1, size);
        for (int i = 0; i < size; i++) {
            std::cout << data1[i] << " ";
        }

        std::cout << std::endl;

        // Demo InsertionSort
        int data2[size];
        FillRandomArray(data2, size, 10, 100);
        insertionSort(data2, size);
        for (int i = 0; i < size; i++) {
            std::cout << data2[i] << " ";
        }

        std::cout << std::endl;

        // Demo Binary Search InsertionSort
        int data3[size];
        FillRandomArray(data3, size, 10, 100);
        binaryInsertionSort(data3, size);
        for (int i = 0; i < size; i++) {
            std::cout << data3[i] << " ";
        }

        std::cout << std::endl;

        int sirWorstCase[size];
        FillSelectionSortWorstCase(sirWorstCase, size);
        printArray(sirWorstCase, size);

        std::cout << std::endl;

        int arrSorted[size];
        FillSortedArray(arrSorted, size);

        printArray(arrSorted, size);

        std::cout << std::endl;

        int arrReverseSorted[size];
        FillReverseSortedArray(arrReverseSorted, size);
        printArray(arrReverseSorted, size);

        std::cout << std::endl;
    }

    TEST_CASE("Direct sorting methods") {
        std::cout << "Testing sorting algorithms...\n\n";

        int data[100];

        FillRandomArray(data, 100, 10, 100);
        bubbleSort(data, 100);
        REQUIRE(IsSorted(data, 100));

        FillRandomArray(data, 100);
        selectionSort(data, 100);
        REQUIRE(IsSorted(data, 100));

        FillRandomArray(data, 100);
        insertionSort(data, 100);
        REQUIRE(IsSorted(data, 100));

        FillRandomArray(data, 100);
        binaryInsertionSort(data, 100);
        REQUIRE(IsSorted(data, 100));


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
        // Write your performance analysis here, as explained in the readme
        // You should use profiler.createOperation to pass the counter to each sorting function

        // fill array with n numbers from [100..10000] with an increment of max 500
        // for each array size count the operations

        std::cout << "Performance of sorting algorithms...\n\n";

        for (int n = 100; n <= 10000; n = n + 100) {
            int arrBubble[n];
            int arrSelection[n];
            int arrInsertion[n];
            int arrBinaryInsert[n];

            auto opAsgBubble = profiler.createOperation("asg_bubble_sort", n);
            auto opCmpBubble = profiler.createOperation("cmp_bubble_sort", n);
            auto opAsgSelection = profiler.createOperation("asg_selection_sort", n);
            auto opCmpSelection = profiler.createOperation("cmp_selection_sort", n);
            auto opAsgInsertion = profiler.createOperation("asg_insertion_sort", n);
            auto opCmpInsertion = profiler.createOperation("cmp_insertion_sort", n);
            auto opAsgBinInsertion = profiler.createOperation("asg_binary_insertion_sort", n);
            auto opCmpBinInsertion = profiler.createOperation("cmp_binary_insertion_sort", n);

            if (whichCase == AVERAGE) {
                for (int j = 0; j < 5; j++) {
                    FillRandomArray(arrBubble, n);
                    memcpy(arrSelection, arrBubble, n * sizeof(int));
                    memcpy(arrInsertion, arrBubble, n * sizeof(int));
                    memcpy(arrBinaryInsert, arrBubble, n * sizeof(int));

                    bubbleSort(arrBubble, n, &opAsgBubble, &opCmpBubble);
                    selectionSort(arrSelection, n, &opAsgSelection, &opCmpSelection);
                    insertionSort(arrInsertion, n, &opAsgInsertion, &opCmpInsertion);
                    binaryInsertionSort(arrBinaryInsert, n, &opAsgBinInsertion, &opCmpBinInsertion);
                }
            } else {
                if (whichCase == BEST) {
                    FillSortedArray(arrBubble, n);
                    FillSortedArray(arrSelection, n);
                    FillSortedArray(arrInsertion, n);
                    FillSortedArray(arrBinaryInsert, n);
                } else if (whichCase == WORST) {
                    FillSelectionSortWorstCase(arrSelection, n);
                    FillReverseSortedArray(arrBubble, n);
                    FillReverseSortedArray(arrInsertion, n);
                    FillReverseSortedArray(arrBinaryInsert, n);
                }

                bubbleSort(arrBubble, n, &opAsgBubble, &opCmpBubble);
                selectionSort(arrSelection, n, &opAsgSelection, &opCmpSelection);
                insertionSort(arrInsertion, n, &opAsgInsertion, &opCmpInsertion);
                binaryInsertionSort(arrBinaryInsert, n, &opAsgBinInsertion, &opCmpBinInsertion);
            }
        }

        if (whichCase == AVERAGE) {
            profiler.divideValues("asg_bubble_sort", 5);
            profiler.divideValues("asg_selection_sort", 5);
            profiler.divideValues("asg_insertion_sort", 5);
            profiler.divideValues("asg_binary_insertion_sort", 5);
            profiler.divideValues("cmp_bubble_sort", 5);
            profiler.divideValues("cmp_selection_sort", 5);
            profiler.divideValues("cmp_insertion_sort", 5);
            profiler.divideValues("cmp_binary_insertion_sort", 5);
        }

        // Assignments
        profiler.createGroup("assignments_all", "asg_bubble_sort", "asg_selection_sort", "asg_insertion_sort",
                             "asg_binary_insertion_sort"); // all
        profiler.createGroup("assignments_binary-insertion_selection", "asg_binary_insertion_sort",
                             "asg_selection_sort"); // binaryInsertion & Selection
        profiler.createGroup("assignments_selection", "asg_selection_sort");

        // Comparisons
        profiler.createGroup("comparisons_all", "cmp_bubble_sort", "cmp_selection_sort", "cmp_insertion_sort",
                             "cmp_binary_insertion_sort"); // all
        profiler.createGroup("comparisons_binary-insertion_selection", "cmp_binary_insertion_sort",
                             "cmp_selection_sort"); // binaryInsertion & Selection
        profiler.createGroup("comparisons_binary-insertion", "cmp_binary_insertion_sort");

        // Total
        profiler.addSeries("total_bubble", "asg_bubble_sort", "cmp_bubble_sort");
        profiler.addSeries("total_selection", "asg_selection_sort", "cmp_selection_sort");
        profiler.addSeries("total_insertion", "asg_insertion_sort", "cmp_insertion_sort");
        profiler.addSeries("total_bin_insert", "asg_binary_insertion_sort", "cmp_binary_insertion_sort");

        profiler.createGroup("total_ops", "total_bubble", "total_selection", "total_insertion", "total_bin_insert");

        profiler.reset("asg_bubble_sort");
        profiler.reset("cmp_bubble_sort");
        profiler.reset("asg_selection_sort");
        profiler.reset("cmp_selection_sort");
        profiler.reset("asg_insertion_sort");
        profiler.reset("cmp_insertion_sort");
        profiler.reset("asg_binary_insertion_sort");
        profiler.reset("cmp_binary_insertion_sort");
    }


    void benchmark(Profiler &profiler, AnalysisCase whichCase) {
        // Write your benchmarks here, as explained in the readme
        // You should use profiler.startTimer/stopTimer for measuring and plotting measured time

        std::cout << "Benchmarking sorting algorithms...\n\n";

        for (int n = 100; n <= 10000; n += 100) {
            if (whichCase == WORST) {
                //! WORST CASE --------------

                // Selection Sort -- WORST
                int arrWorstSelection[n];
                FillSelectionSortWorstCase(arrWorstSelection, n);
                profiler.startTimer("worst_selection_sort", n);
                selectionSort(arrWorstSelection, n);
                profiler.stopTimer("worst_selection_sort", n);

                // Bubble Sort -- WORST
                int arrWorstBubble[n];
                FillReverseSortedArray(arrWorstBubble, n);
                profiler.startTimer("worst_bubble_sort", n);
                bubbleSort(arrWorstBubble, n);
                profiler.stopTimer("worst_bubble_sort", n);

                // Insertion Sort -- WORST
                int arrWorstInsertion[n];
                FillReverseSortedArray(arrWorstInsertion, n);
                profiler.startTimer("worst_insertion_sort", n);
                insertionSort(arrWorstInsertion, n);
                profiler.stopTimer("worst_insertion_sort", n);

                // Binary Insertion Sort -- WORST
                int arrWorstBinaryInsertion[n];
                FillReverseSortedArray(arrWorstBinaryInsertion, n);
                profiler.startTimer("worst_binary_insert_sort", n);
                binaryInsertionSort(arrWorstBinaryInsertion, n);
                profiler.stopTimer("worst_binary_insert_sort", n);
            } else if (whichCase == BEST) {
                //! BEST CASE --------------

                // Selection Sort -- BEST
                int arrBestSelection[n];
                FillSortedArray(arrBestSelection, n);
                profiler.startTimer("best_selection_sort", n);
                selectionSort(arrBestSelection, n);
                profiler.stopTimer("best_selection_sort", n);

                // Bubble Sort -- BEST
                int arrBestBubble[n];
                FillSortedArray(arrBestBubble, n);
                profiler.startTimer("best_bubble_sort", n);
                bubbleSort(arrBestBubble, n);
                profiler.stopTimer("best_bubble_sort", n);

                // Insertion Sort -- BEST
                int arrBestInsertion[n];
                FillSortedArray(arrBestInsertion, n);
                profiler.startTimer("best_insertion_sort", n);
                insertionSort(arrBestInsertion, n);
                profiler.stopTimer("best_insertion_sort", n);

                // Binary Insertion Sort -- BEST
                int arrBestBinaryInsert[n];
                FillSortedArray(arrBestBinaryInsert, n);
                profiler.startTimer("best_binary_insertion_sort", n);
                binaryInsertionSort(arrBestBinaryInsert, n);
                profiler.stopTimer("best_binary_insertion_sort", n);
            } else {
                //! AVERAGE CASE ---------------------------------
                int arrAvgSelection[n];
                FillRandomArray(arrAvgSelection, n);

                int arrAvgBubble[n];
                memcpy(arrAvgBubble, arrAvgSelection, n * sizeof(int));

                int arrAvgInsertion[n];
                memcpy(arrAvgInsertion, arrAvgSelection, n * sizeof(int));

                int arrAvgBinaryInsert[n];
                memcpy(arrAvgBinaryInsert, arrAvgSelection, n * sizeof(int));

                // Selection Sort -- AVERAGE
                profiler.startTimer("avg_selection_sort", n);
                selectionSort(arrAvgSelection, n);
                profiler.stopTimer("avg_selection_sort", n);

                // Bubble Sort -- AVERAGE
                profiler.startTimer("avg_bubble_sort", n);
                bubbleSort(arrAvgBubble, n);
                profiler.stopTimer("avg_bubble_sort", n);

                // Insertion Sort -- AVERAGE
                profiler.startTimer("avg_insertion_sort", n);
                insertionSort(arrAvgInsertion, n);
                profiler.stopTimer("avg_insertion_sort", n);

                // Binary Insertion Sort -- AVERAGE
                profiler.startTimer("avg_binary_insert_sort", n);
                binaryInsertionSort(arrAvgBinaryInsert, n);
                profiler.stopTimer("avg_binary_insert_sort", n);
            }
        }
        profiler.createGroup("time_average", "avg_selection_sort", "avg_bubble_sort", "avg_insertion_sort",
                             "avg_binary_insert_sort");
        profiler.createGroup("time_best", "best_selection_sort", "best_bubble_sort", "best_insertion_sort",
                             "best_binary_insertion_sort");
        profiler.createGroup("time_worst", "worst_selection_sort", "worst_bubble_sort", "worst_insertion_sort",
                             "worst_binary_insert_sort");
        profiler.createGroup("time_best__BinaryInsert_and_BubbleSort", "best_bubble_sort",
                             "best_binary_insertion_sort");
    }
} // namespace lab01
