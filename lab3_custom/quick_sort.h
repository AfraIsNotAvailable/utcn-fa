#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include "Profiler.h"
#include "commandline.h"

using namespace std;

namespace lab03
{

	/**
	 * @brief Quick sort algorithm
	 *
	 * @param values array of input values to be sorted
	 * @param opAsg optional counter for assignment operations
	 * @param opCmp optional counter for comparison operations
	 */
	void quickSort(int *values, int low, int high, Operation* opAsg = nullptr, Operation* opCmp = nullptr);

	/**
	 * @brief Hybridized Quick sort algorithm
	 *
	 * @param values array of input values to be sorted
	 * @param n number of values in the input array
	 * @param opAsg optional counter for assignment operations
	 * @param opCmp optional counter for comparison operations
	 */
	void hybridizedQuickSort(int* values, int n, Operation* opAsg = nullptr, Operation* opCmp = nullptr);

	/**
	 * @brief Quick select algorithm
	 *
	 * @param values array of input values to be sorted
	 * @param low
	 * @param high
	 * @param sel
	 * @param opAsg optional counter for assignment operations
	 * @param opCmp optional counter for comparison operations
	 */
		void quickSelect(int* values, int low, int high, int sel, Operation* opAsg = nullptr, Operation* opCmp = nullptr);

	/**
	 * @brief Heap sort algorithm
	 *
	 * @param values array of input values to be sorted
	 * @param n number of values in the input array
	 * @param opAsg optional counter for assignment operations
	 * @param opCmp optional counter for comparison operations
	 */
	void heapSort(int* values, int n, Operation* opAsg = nullptr, Operation* opCmp = nullptr);


	/**
	 * @brief Demo code for the sorting algorithms
	 *
	 * @param size number of elements to demonstrate on
	 */
	void demonstrate(int size);

	/**
	 * @brief Performance analysis for the sorting algorithms
	 *
	 * @param profiler profiler to use
	 * @param whichCase one of AVERAGE, BEST or WORST cases
	 */
	void performance(Profiler& profiler, AnalysisCase whichCase);

	/**
	 * @brief Benchmarking for the sorting algorithms
	 *
	 * @param profiler profiler to use
	 * @param whichCase one of AVERAGE, BEST or WORST cases
	 */
	void benchmark(Profiler& profiler, AnalysisCase whichCase);

} // namespace lab03

#endif // __QUICK_SORT_H__