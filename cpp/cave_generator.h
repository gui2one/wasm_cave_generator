#ifndef CAVE_GENRATOR_H
#define CAVE_GENRATOR_H
#include <stdio.h>
#include <vector>
#include <emscripten.h>
#include "grid.h"
#include "flood_fill.h"

class CaveGenerator
{
public:
    Grid m_grid;
    std::vector<int> cells;
    int m_seed;

    int m_smooth_iterations = 10;

    int threshold = 150;

public:
    CaveGenerator();

    int getWidth() { return m_grid.m_resx; }
    void setWidth(int value) { m_grid.setResX(value); }

    int getHeight() { return m_grid.m_resy; }
    void setHeight(int value) { m_grid.setResY(value); }

    void setThreshold(int value) { threshold = value; }

    void setRandomSeed(int seed) { m_seed = seed; }
    void fillRandom();

    void inspect();

    int getCellByCoords(int x, int y, std::vector<int> &cur_cells);

    int getCellIndex(int x, int y);

    int getNumNeighbours(int index);

    void setSmoothIterations(int num) { m_smooth_iterations = num; };

    void smooth(int iterations);

    std::vector<int> make_blob(Grid &grid, int mask_value, std::vector<int> &_filled_cells);

    std::vector<int> generate();

private:
};
#endif /* CAVE_GENRATOR_H */