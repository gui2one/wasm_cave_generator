#include "flood_fill.h"
#include <emscripten/bind.h>

namespace FloodFill2
{

    void push(std::vector<int> &stack, int x, int y)
    {
        stack.push_back(x);
        stack.push_back(y);
    }

    bool pop(std::vector<int> &stack, int &x, int &y)
    {
        if (stack.size() < 2)
        {

            return false;
        }
        y = stack.back();
        stack.pop_back();
        x = stack.back();
        stack.pop_back();

        return true;
    }

    EMSCRIPTEN_KEEPALIVE
    void floodFill4Stack(std::vector<int> &screenBuffer, int w, int h, int x, int y, int newColor, int oldColor)
    {
        if (newColor == oldColor)
            return; //avoid infinite loop

        static const int dx[4] = {0, 1, 0, -1}; // relative neighbor x coordinates
        static const int dy[4] = {-1, 0, 1, 0}; // relative neighbor y coordinates

        std::vector<int> stack;
        push(stack, x, y);

        // std::cout << "filling" << std::endl;
        while (pop(stack, x, y))
        {
            screenBuffer[y * w + x] = newColor;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < w && ny >= 0 && ny < h && screenBuffer[ny * w + nx] == oldColor)
                {
                    push(stack, nx, ny);
                }
            }
        }
    }
};

EMSCRIPTEN_BINDINGS(FloodFill2)
{
    emscripten::function("floodFill4Stack", &FloodFill2::floodFill4Stack);
}