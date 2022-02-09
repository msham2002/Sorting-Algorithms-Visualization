#include<ctime>
#include<SDL.h>
#include<iostream>
#include"DataPoint.h"
#include"Sort.h"

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;
SDL_Renderer* renderer = NULL;

void Init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Sorting Algorithms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(window);
}

void close() {
    screen = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_Quit();
}

int main(int argc, char* args[]) {
    srand(time(NULL));
    std::vector<int> values((SCREEN_WIDTH / 5) + 1);
    std::vector<DataPoint> dataPoints = Generate(values, dataPoints);
    bool quit = false;
    SDL_Event e;

    std::cout << "This program contains visualizations of several different sorting algorithms. Some algorithms have been slowed down to make it easier to watch them. Press ENTER to begin" << std::endl;
    std::cin.get();

    std::cout << "[0] Random Data\n"
        << "[1] Bubble Sort\n"
        << "[2] Selection Sort\n"
        << "[3] Insertion Sort\n"
        << "[4] Merge Sort\n"
        << "[5] Radix Sort\n"
        << "[6] Quick Sort\n"
        << "[7] Bitonic Sort\n"
        << "[8] Heap Sort\n";

    Init();
    //program loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;

            else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                case SDLK_0:
                    dataPoints = Generate(values, dataPoints);
                    break;
                case SDLK_1:
                    BubbleSort(dataPoints);
                    break;
                case SDLK_2:
                    SelectionSort(dataPoints);
                    break;
                case SDLK_3:
                    InsertionSort(dataPoints);
                    break;
                case SDLK_4:
                    MergeSort(dataPoints, 0, dataPoints.size() - 1);
                    break;
                case SDLK_5:
                    RadixSort(dataPoints);
                    break;
                case SDLK_6:
                    QuickSort(dataPoints, 0, dataPoints.size() - 1);
                    break;
                case SDLK_7:
                    BitonicSort(dataPoints, 0, dataPoints.size(), 1);
                    break;
                case SDLK_8:
                    HeapSort(dataPoints, dataPoints.size());
                    break;
                }
            }
        }
        Visualization(dataPoints);
    }
    close();
    return 0;
}