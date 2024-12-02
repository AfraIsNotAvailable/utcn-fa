//
// Created by afra-laptop on 11/22/2024.
//

#ifndef DYNAMIC_H
#define DYNAMIC_H
#include <commandline.h>
#include <Profiler.h>

namespace lab7
{
    void demonstrate();
    void performance(Profiler& profiler, const AnalysisCase whichCase);
    void benchmark(Profiler& profiler, const AnalysisCase whichCase);
}

#endif //DYNAMIC_H
