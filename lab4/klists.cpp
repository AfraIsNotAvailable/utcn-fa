#include "klists.h"

#include <cmath>
#include <commandline.h>

/**
 * Operatiile pentru cand `n` variaza intre 100 si 10000 au o crestere liniara O(n)
 * Operatiile pentru cand `k` variaza intre 100 si 500 au creste logaritmica o(logn)
 */
namespace lab04 {
    struct HeapNode {
        int key; // Value of the element
        int listIndex; // Index of list from which element came
        int elemIndex; // Index of next element in the list
    };

    void minHeapify(HeapNode A[], int size, int index, Operation *opCmp = nullptr, Operation *opAsg = nullptr) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (opCmp) opCmp->count(1);
        if (left < size && A[left].key < A[smallest].key)
            smallest = left;

        if (opCmp) opCmp->count(1);
        if (right < size && A[right].key < A[smallest].key)
            smallest = right;

        if (opCmp) opCmp->count(1);
        if (smallest != index) {
            if (opAsg) opAsg->count(3);
            std::swap(A[index], A[smallest]);
            minHeapify(A, size, smallest, opCmp, opAsg);
        }
    }

    int *mergeKLists(int **lists, int k, int n, Operation *opCmp = nullptr, Operation *opAsg = nullptr) {
        int totalElements = n;
        int *outList = (int *) malloc(totalElements * sizeof(int));
        if (!outList) return nullptr;

        HeapNode *harr = new HeapNode[k];
        int validLists = 0;

        for (int i = 0; i < k; i++) {
            if (lists[i]) {
                harr[validLists].key = lists[i][0];
                harr[validLists].listIndex = i;
                harr[validLists].elemIndex = 1;
                validLists++;
            }
        }

        for (int i = (validLists - 1) / 2; i >= 0; i--)
            minHeapify(harr, validLists, i, opCmp, opAsg);

        for (int i = 0; i < totalElements; i++) {
            if (validLists == 0) break;

            HeapNode root = harr[0];
            outList[i] = root.key;

            int listIdx = root.listIndex;
            int elemIdx = root.elemIndex;

            int elementsInThisList = n / k + (listIdx < (n % k) ? 1 : 0);

            if (opCmp) opCmp->count(1);
            if (elemIdx < elementsInThisList) {
                if (opAsg) opAsg->count(2);
                harr[0].key = lists[listIdx][elemIdx];
                harr[0].elemIndex = elemIdx + 1;
            } else {
                if (opAsg) opAsg->count(1);
                harr[0] = harr[validLists - 1];
                validLists--;
            }

            if (validLists > 0)
                minHeapify(harr, validLists, 0, opCmp, opAsg);
        }

        delete[] harr;
        return outList;
    }

    void generateLists(int n, int k, int **lists, int *array/* = nullptr*/) {
        int rest = n % k;

        if (array) {
            int l = 0; // for array
            for (int i = 0; i < k; i++) {
                int elementsInThisList = n / k + (i < rest ? 1 : 0);
                lists[i] = (int *) calloc(elementsInThisList, sizeof(int));

                if (!lists[i]) {
                    for (int j = 0; j < i; j++) {
                        free(lists[j]);
                    }
                    return;
                }

                // for (int j = 0; j < elementsInThisList; j++) {
                //     lists[i][j] = array[l++];
                // }

                memcpy(lists[i], array + l, elementsInThisList * sizeof(int));
                l += elementsInThisList;
            }
        } else {
            for (int i = 0; i < k; i++) {
                int elementsInThisList = n / k + (i < rest ? 1 : 0);
                lists[i] = (int *) calloc(elementsInThisList, sizeof(int));

                if (!lists[i]) {
                    for (int j = 0; j < i; j++) {
                        free(lists[j]);
                    }
                    return;
                }

                FillRandomArray(lists[i], elementsInThisList, 10, 50000, false, ASCENDING);
            }
        }
    }

    void printLists(int n, int k, int **lists) {
        for (int i = 0; i < k; i++) {
            int digits = (k == 0) ? 1 : (int) (log10(k) + 1);
            printf("[%0*d]:  ", digits, i);
            int elementsInThisList = n / k + (i < (n % k) ? 1 : 0);
            for (int j = 0; j < elementsInThisList; j++) {
                printf("%5d  ", lists[i][j]);
            }
            printf("\n");
        }
    }

    void demonstrate(int n, int k) {
        int **lists = (int **) malloc(k * sizeof(int *));
        if (!lists) {
            printf("Memory allocation failed\n");
            return;
        }

        // int array[] = {12, 34, 56, 23, 24, 36, 17, 29, 47, 73, 51, 73, 85, 96, 9};

        // generateLists(15, 4, lists, array);

        generateLists(n, k, lists);

        printf("\b");

        printLists(n, k, lists);

        printf("\noutlist: ");

        int *outList = mergeKLists(lists, k, n);

        for (int i = 0; i < n; i++) {
            printf("%d ", outList[i]);
        }

        for (int i = 0; i < k; i++) {
            free(lists[i]);
        }
        free(lists);
    }

    void performance(Profiler &profiler, AnalysisCase whichCase) {
        // TODO: Implement performance testing

        for (int steps = 0; steps < 3; steps++) {
            int k1 = 5, k2 = 10, k3 = 100;
            for (int n = 100; n <= 10000; n += 100) {
                int n1 = n * k1;
                int n2 = n * k2;
                int n3 = n * k3;
                int **lists1 = (int **) malloc(k1 * sizeof(int *));
                int **lists2 = (int **) malloc(k2 * sizeof(int *));
                int **lists3 = (int **) malloc(k3 * sizeof(int *));

                if (!lists1 or !lists2 or !lists3) {
                    printf("Memory allocation failed\n");
                    return;
                }

                generateLists(n1, k1, lists1);
                generateLists(n2, k2, lists2);
                generateLists(n3, k3, lists3);

                auto opAsg1 = profiler.createOperation("asg1", n);
                auto opCmp1 = profiler.createOperation("cmp1", n);
                auto opAsg2 = profiler.createOperation("asg2", n);
                auto opCmp2 = profiler.createOperation("cmp2", n);
                auto opAsg3 = profiler.createOperation("asg3", n);
                auto opCmp3 = profiler.createOperation("cmp3", n);

                int *outlist1 = mergeKLists(lists1, k1, n1, &opCmp1, &opAsg1);
                int *outlist2 = mergeKLists(lists2, k2, n2, &opCmp2, &opAsg2);
                int *outlist3 = mergeKLists(lists3, k3, n3, &opCmp3, &opAsg3);

                for (int i = 0; i < k1; i++) {
                    free(lists1[i]);
                }
                free(lists1);
                for (int i = 0; i < k2; i++) {
                    free(lists2[i]);
                }
                free(lists2);
                for (int i = 0; i < k3; i++) {
                    free(lists3[i]);
                }
                free(lists3);
            }
        }
        profiler.addSeries("k_5", "asg1", "cmp1");
        profiler.addSeries("k_10", "asg2", "cmp2");
        profiler.addSeries("k_100", "asg3", "cmp3");

        profiler.divideValues("k_5", 5);
        profiler.divideValues("k_10", 10);
        profiler.divideValues("k_100", 100);

        profiler.createGroup("Operations variable n", "k_5", "k_10", "k_100");

        for (int k = 10; k <= 500; k += 10) {
            int **lists = (int **) malloc(k * sizeof(int *));
            if (!lists) {
                printf("Memory allocation failed\n");
                return;
            }

            generateLists(10000, k, lists);

            auto opAsg = profiler.createOperation("asg", k);
            auto opCmp = profiler.createOperation("cmp", k);

            int *outlist = mergeKLists(lists, k, 10000, &opCmp, &opAsg);

            for (int i = 0; i < k; i++) {
                free(lists[i]);
            }
            free(lists);
        }

        profiler.addSeries("ops", "asg", "cmp");
        profiler.createGroup("Operations variable k", "ops");
    }

    void benchmark(Profiler &profiler, AnalysisCase whichCase) {
        // TODO: Implement benchmarking
    }
}
