#include"Sort.h"

std::vector<DataPoint> Generate(std::vector<int> values, std::vector<DataPoint> dataPoints) {
    int h, idx;
    int H = 10;
    std::vector<DataPoint> empty;
    dataPoints = empty;
    //fill values vector with heights
    for (int i = 1; i < values.size(); ++i) {
        values[i] = 10 + H;
        H += 2;
    }
    //create random data points from values vector, removing an element each time a new data point is created
    for (int i = 0; i < SCREEN_WIDTH - 4; i += 5) {
        idx = rand() % (values.size() - 1) + 1;
        h = values[idx];
        values.erase(values.begin() + idx);
        DataPoint D(h, i, SCREEN_HEIGHT - h);
        dataPoints.push_back(D);
    }
    return dataPoints;
}

//swap data points
void Swap(DataPoint* A, DataPoint* B) {
    DataPoint temp = *A;
    *A = *B;
    *B = temp;
}

//draw and render datapoints
void Visualization(std::vector<DataPoint> dataPoints, int idx, int idx2) {
    SDL_PumpEvents();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int k = 0; k < dataPoints.size(); ++k)
        dataPoints[k].render();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    if (idx != -1)
        dataPoints[idx].render();
    if (idx2 != -1)
        dataPoints[idx2].render();

    SDL_RenderPresent(renderer);
}

//sorting algorithms
void BubbleSort(std::vector<DataPoint>& dataPoints) {
    bool swapped;
    for (int i = 0; i < dataPoints.size() - 1; ++i) {
        swapped = false;
        for (int j = 0; j < dataPoints.size() - i - 1; ++j) {
            if (dataPoints[j].height > dataPoints[j + 1].height) {
                SDL_Delay(1);
                Swap(&dataPoints[j], &dataPoints[j + 1]);
                Visualization(dataPoints, j, j + 1);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void SelectionSort(std::vector<DataPoint>& dataPoints) {
    int min;
    DataPoint key;
    for (int i = 0; i < dataPoints.size() - 1; ++i) {
        min = i;
        for (int j = i + 1; j < dataPoints.size(); ++j) {
            if (dataPoints[min].height > dataPoints[j].height) {
                min = j;
            }

            key = dataPoints[min];
            while (min > i) {
                SDL_Delay(1);
                dataPoints[min] = dataPoints[min - 1];
                Visualization(dataPoints, min);
                min--;
            }
            dataPoints[i] = key;
        }
    }
}

void InsertionSort(std::vector<DataPoint>& dataPoints) {
    DataPoint key;
    int j;
    for (int i = 1; i < dataPoints.size(); ++i) {
        key = dataPoints[i];
        j = i - 1;
        while (j >= 0 && dataPoints[j].height > key.height) {
            SDL_Delay(1);
            dataPoints[j + 1] = dataPoints[j];
            Visualization(dataPoints, j);
            --j;
        }
        dataPoints[j + 1] = key;
    }
}

void MergeSort(std::vector<DataPoint>& dataPoints, int begin, int end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    MergeSort(dataPoints, begin, mid);
    MergeSort(dataPoints, mid + 1, end);
    Merge(dataPoints, begin, mid, end);
}

void Merge(std::vector<DataPoint>& dataPoints, int left, int mid, int right) {
    int subOne = mid - left + 1;
    int subTwo = right - mid;
    std::vector<DataPoint>L(subOne);
    std::vector<DataPoint>R(subTwo);

    for (int i = 0; i < subOne; ++i) {
        SDL_Delay(5);
        L[i] = dataPoints[left + i];
        Visualization(dataPoints, left + i);
    }
    for (int j = 0; j < subTwo; ++j) {
        ;
        SDL_Delay(5);
        R[j] = dataPoints[mid + 1 + j];
        Visualization(dataPoints, mid + 1 + j);
    }

    int i = 0, j = 0;
    int k = left;

    while (i < subOne && j < subTwo) {
        if (L[i].height <= R[j].height) {
            SDL_Delay(5);
            dataPoints[k] = L[i];
            Visualization(dataPoints, k);
            i++;
        }
        else {
            SDL_Delay(5);
            dataPoints[k] = R[j];
            Visualization(dataPoints, k);
            j++;
        }
        k++;
    }

    while (i < subOne) {
        SDL_Delay(5);
        dataPoints[k] = L[i];
        Visualization(dataPoints, k);
        i++;
        k++;
    }

    while (j < subTwo) {
        SDL_Delay(5);
        dataPoints[k] = R[j];
        Visualization(dataPoints, k);
        j++;
        k++;
    }

    Visualization(dataPoints);
}

void CountSort(std::vector<DataPoint>& dataPoints, int exp) {
    std::vector<DataPoint> output(dataPoints.size());
    int count[10] = { 0 };

    for (int i = 0; i < dataPoints.size(); ++i) {
        count[(dataPoints[i].height / exp) % 10]++;
    }

    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = dataPoints.size() - 1; i >= 0; --i) {
        SDL_Delay(5);
        output[count[(dataPoints[i].height / exp) % 10] - 1] = dataPoints[i];
        count[(dataPoints[i].height / exp) % 10]--;
    }

    for (int i = 0; i < dataPoints.size(); ++i) {
        SDL_Delay(10);
        dataPoints[i] = output[i];
        Visualization(dataPoints);
    }
}

void RadixSort(std::vector<DataPoint>& dataPoints) {
    int max = dataPoints[0].height;
    for (int i = 1; i < dataPoints.size(); ++i) {
        if (dataPoints[i].height > max) {
            max = dataPoints[i].height;
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        CountSort(dataPoints, exp);
        Visualization(dataPoints);
    }
}

int Partition(std::vector<DataPoint>& dataPoints, int low, int high) {
    int pivot = dataPoints[high].height;
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (dataPoints[j].height < pivot) {
            i++;
            SDL_Delay(10);
            Swap(&dataPoints[i], &dataPoints[j]);
            Visualization(dataPoints, j);
        }
    }
    SDL_Delay(10);
    Swap(&dataPoints[i + 1], &dataPoints[high]);
    Visualization(dataPoints);
    return (i + 1);
}

void QuickSort(std::vector<DataPoint>& dataPoints, int low, int high) {
    if (low < high) {
        int pi = Partition(dataPoints, low, high);
        QuickSort(dataPoints, low, pi - 1);
        QuickSort(dataPoints, pi + 1, high);
    }
}


void BitonicMerge(std::vector<DataPoint>& dataPoints, int low, int count, int dir) {
    if (count > 1) {
        int k = count / 2;
        for (int i = low; i < low + k; ++i) {
            if (dir == (dataPoints[i].height > dataPoints[i + k].height)) {
                SDL_Delay(10);
                Swap(&dataPoints[i], &dataPoints[i + k]);;
                Visualization(dataPoints, i, i + k);
            }
        }
        BitonicMerge(dataPoints, low, k, dir);
        BitonicMerge(dataPoints, low + k, k, dir);
    }
}

void BitonicSort(std::vector<DataPoint>& dataPoints, int low, int count, int dir) {
    if (count > 1) {
        int k = count / 2;
        BitonicSort(dataPoints, low, k, 1);
        BitonicSort(dataPoints, low + k, k, 0);
        BitonicMerge(dataPoints, low, count, dir);
    }
}

void Heap(std::vector<DataPoint>& dataPoints, int n, int i) {
    int high = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && dataPoints[l].height > dataPoints[high].height) {
        SDL_Delay(5);
        high = l;
    }

    if (r < n && dataPoints[r].height > dataPoints[high].height) {
        SDL_Delay(5);
        high = r;
    }

    if (high != i) {
        SDL_Delay(5);
        Swap(&dataPoints[i], &dataPoints[high]);
        Visualization(dataPoints, i);
        Heap(dataPoints, n, high);
    }
}

void HeapSort(std::vector<DataPoint>& dataPoints, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        Heap(dataPoints, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        SDL_Delay(5);
        Swap(&dataPoints[0], &dataPoints[i]);
        Visualization(dataPoints, i);
        Heap(dataPoints, i, 0);
    }
}