//
// Created by afras on 04/11/2024.
//

#include "hashtables.h"

namespace lab5 {
    typedef struct {
        int key;
        char name[30];
    } Entry;

    int h(int key, int m) {
        return key % m;
    }

    int hash(int key, int i, int m) {
        return (h(key, m) + 3 * i * i + 5 * i + 7) % m;
    }

    bool insert(Entry *table, int key, int m) {
        int i = 0;

        do {
            int insertIdx = hash(key, i, m);
            if (table[insertIdx].key == -1) {
                table[insertIdx].key = key;
                return true;
            }
            i++;
        } while (i != m);
        return false;
    }

    void printTable(Entry *table, int m) {
        int i = 0;
        printf("table:\n");
        while (i != m - 1) {
            if (table[i].key == -1) {
                char foo[] = "___";
                printf("[%s]", foo);
            } else {
                printf("[%3d]", table[i].key);
            }
            i++;
        }
        printf("\n");
    }

    void init(Entry *table, int m) {
        for (int i = 0; i < m; i++) {
            table[i].key = -1;
        }
    }

    void demonstrate(int n, int k) {
        printf("\b");

        Entry table[10];
        init(table, 10);
        insert(table, 12, 10);
        insert(table, 3, 10);
        insert(table, 24, 10);
        insert(table, 50, 10);
        insert(table, 13, 10);
        printTable(table, 10);
    }

    void performance(Profiler &profiler, AnalysisCase whichCase) {
        //TODO implement performance
    }

    void benchmark(Profiler &profiler, AnalysisCase whichCase) {
        //TODO bench
    }
}
