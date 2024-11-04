//
// Created by afras on 31/10/2024.
//

#ifndef KLISTS_H
#define KLISTS_H

#include "Profiler.h"
#include <commandline.h>


namespace lab04 {
    void generateLists(int n, int k, int** lists, int *array = nullptr);

    void demonstrate(int n, int k);

    void performance(Profiler &profiler, AnalysisCase whichCase);

    void benchmark(Profiler &profiler, AnalysisCase whichCase);
}


#endif //KLISTS_H
