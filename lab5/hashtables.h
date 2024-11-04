//
// Created by afras on 04/11/2024.
//

#ifndef HASHTABLES_H
#define HASHTABLES_H
#include <commandline.h>
#include <Profiler.h>

namespace lab5 {
    void demonstrate(int n, int k);

    void performance(Profiler &profiler, AnalysisCase whichCase);

    void benchmark(Profiler &profiler, AnalysisCase whichCase);
}

#endif //HASHTABLES_H
