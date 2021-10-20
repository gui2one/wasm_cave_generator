#ifndef FLOOD_FILL_H
#define FLOOD_FILL_H
#include <iostream>
#include <emscripten.h>
#include <vector>
namespace FloodFill2
{

    void push(std::vector<int> &stack, int x, int y);

    bool pop(std::vector<int> &stack, int &x, int &y);
    void floodFill4Stack(std::vector<int> &screenBuffer, int w, int h, int x, int y, int newColor, int oldColor);
};
#endif /* FLOOD_FILL_H */