//
// Created by afras on 13/11/2024.
//

#ifndef MULTIWAY_H
#define MULTIWAY_H

#include "Profiler.h"
#include <commandline.h>


namespace lab6 {
    void demonstrate();

    void performance(Profiler &profiler, AnalysisCase whichCase);

    void benchmark(Profiler &profiler, AnalysisCase whichCase);
}
#endif //MULTIWAY_H
