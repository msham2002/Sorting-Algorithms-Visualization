#pragma once

#include "DataPoint.h"

std::vector<DataPoint> Generate(std::vector<int> values, std::vector<DataPoint> dataPoints);
void Swap(DataPoint* A, DataPoint* B);
void Visualization(std::vector<DataPoint> dataPoints, int idx = -1, int idx2 = -1);
void BubbleSort(std::vector<DataPoint>& dataPoints);
void SelectionSort(std::vector<DataPoint>& dataPoints);
void InsertionSort(std::vector<DataPoint>& dataPoints);
void MergeSort(std::vector<DataPoint>& dataPoints, int begin, int end);
void Merge(std::vector<DataPoint>& dataPoints, int begin, int mid, int end);
void CountSort(std::vector<DataPoint>& dataPoints, int exp);
void RadixSort(std::vector<DataPoint>& dataPoints);
int Partition(std::vector<DataPoint>& dataPonts, int low, int high);
void QuickSort(std::vector<DataPoint>& dataPoints, int low, int hight);
void BitonicMerge(std::vector<DataPoint>& dataPoints, int low, int count, int dir);
void BitonicSort(std::vector<DataPoint>& dataPoints, int low, int count, int dir);
void Heap(std::vector<DataPoint>& dataPoints, int n, int i);
void HeapSort(std::vector<DataPoint>& dataPoints, int n);

