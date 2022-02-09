#include"DataPoint.h"

DataPoint::DataPoint() {
    height = 0;
    width = 0;
    posX = 0;
    posY = 0;
}

DataPoint::DataPoint(int h, int x, int y) {
    width = 4;
    height = h;
    posX = x;
    posY = y;
}


void DataPoint::render() {
    rect = { posX, posY, width, height };
    SDL_RenderFillRect(renderer, &rect);
}


DataPoint& DataPoint::operator=(const DataPoint& d) {
    height = d.height;
    posY = SCREEN_HEIGHT - height;
    return *this;
}
