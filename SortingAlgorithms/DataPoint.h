#pragma once

#include<iostream>
#include<SDL.h>
#include<vector>

extern SDL_Window* window;
extern SDL_Surface* screen;
extern SDL_Renderer* renderer;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class DataPoint {
private:
    int width;
    SDL_Rect rect;
public:
    int height, posX, posY;
    DataPoint();
    DataPoint(int h, int x, int y);
    DataPoint& operator = (const DataPoint& d);;
    void render();
};