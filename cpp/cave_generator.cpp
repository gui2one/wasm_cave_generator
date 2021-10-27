#include "cave_generator.h"
#include "emscripten/bind.h"
#include <cstdlib>
#include <iostream>
#include <chrono>

// using namespace emscripten;

EMSCRIPTEN_KEEPALIVE
CaveGenerator::CaveGenerator()
{
    m_seed = 0;
    m_grid.setResX(32);
    m_grid.setResY(32);
    printf("--- C++ Cave Generator ---\n");
    for (size_t j = 0; j < m_grid.m_resy; j++)
    {
        for (size_t i = 0; i < m_grid.m_resx; i++)
        {
            cells.push_back(0);
        }
    }

    // printf("CaveGenerator !!!! Fuck Yeah !!!!\n");
}

EMSCRIPTEN_KEEPALIVE
void CaveGenerator::fillRandom()
{
    auto secs = std::chrono::system_clock::now().time_since_epoch();
    // std::srand(secs.count());
    std::srand(m_seed);
    std::vector<int> values;
    for (size_t y = 0; y < m_grid.m_resy; y++)
    {
        for (size_t x = 0; x < m_grid.m_resx; x++)
        {
            int index = y * 4 + x;
            int rand_value = double(std::rand()) / (RAND_MAX)*256;
            values.push_back(rand_value > threshold ? 255 : 0);
        }
        /* code */
    }

    m_grid.m_cells = values;
}

// EMSCRIPTEN_KEEPALIVE
void CaveGenerator::smooth(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {

        std::vector<int> cells_copy(m_grid.m_cells);
        for (int y = 0; y < m_grid.m_resy; y++)
        {
            for (int x = 0; x < m_grid.m_resx; x++)
            {
                int index = getCellIndex(x, y);
                int num = getNumNeighbours(index);

                if (num > 4)
                {
                    cells_copy[index] = 255;
                }
                else if (num < 4)
                {
                    cells_copy[index] = 0;
                }

                if (x == 0 || x == m_grid.m_resx - 1 || y == 0 || y == m_grid.m_resy - 1)
                {
                    cells_copy[index] = 0;
                }
            }
        }

        m_grid.m_cells = cells_copy;
    }
}

std::vector<int> CaveGenerator::make_blob(Grid &grid, int mask_value, std::vector<int> &_filled_cells)
{
    std::vector<int> blob;
    blob.reserve(grid.m_cells.size());
    for (int y = 0; y < grid.m_resy; y++)
    {
        for (int x = 0; x < grid.m_resx; x++)
        {
            int index = y * grid.m_resx + x;
            int val = 0;
            if (grid.m_cells[index] == mask_value)
            {
                val = 255;
            }
            blob.emplace_back(val);

            if (grid.m_cells[index] == mask_value)
            {
                _filled_cells[index] = 255;
            }
        }
    }

    return blob;
}

void CaveGenerator::inspect()
{
    // blobs are here to collect the different filled areas
    std::vector<std::vector<int>> blobs;

    Grid grid_copy(m_grid);
    std::vector<int> filled_cells(grid_copy.m_cells);
    std::fill(filled_cells.begin(), filled_cells.end(), 0);

    int fill_value = 128;

    for (int y = 0; y < m_grid.m_resy; y++)
    {
        for (int x = 0; x < m_grid.m_resx; x++)
        {
            int index = y * m_grid.m_resx + x;
            if (filled_cells[index] != 255)
            {

                FloodFill2::floodFill4Stack(grid_copy.m_cells, m_grid.m_resx, m_grid.m_resy, x, y, fill_value, m_grid.m_cells[index]);

                auto blob = make_blob(grid_copy, fill_value, filled_cells);
                blobs.push_back(blob);
            }
        }
    }

    std::cout << "Blob count : " << blobs.size() << std::endl;
    // m_grid.m_cells = cells;
}

// EMSCRIPTEN_KEEPALIVE
int CaveGenerator::getCellByCoords(int x, int y, std::vector<int> &cur_cells)
{
    int index = y * m_grid.m_resx + x;
    return cur_cells[index];
}

// EMSCRIPTEN_KEEPALIVE
int CaveGenerator::getCellIndex(int x, int y)
{
    int index = y * m_grid.m_resx + x;
    return index;
}

// EMSCRIPTEN_KEEPALIVE
int CaveGenerator::getNumNeighbours(int index)
{
    int x = index % m_grid.m_resx;
    int y = index / m_grid.m_resx;
    int num = 0;
    if (x > 0 && x < m_grid.m_resx && y > 0 && y < m_grid.m_resy)
    {
        int cur_cell = getCellByCoords(x, y - 1, m_grid.m_cells);
        if (cur_cell > 128)
            num++;

        cur_cell = getCellByCoords(x + 1, y - 1, m_grid.m_cells);
        if (cur_cell > 128)
            num++;

        cur_cell = getCellByCoords(x + 1, y, m_grid.m_cells);
        if (cur_cell > 128)
            num++;

        cur_cell = getCellByCoords(x + 1, y + 1, m_grid.m_cells);
        if (cur_cell > 128)
            num++;

        cur_cell = getCellByCoords(x, y + 1, m_grid.m_cells);
        if (cur_cell > 128)
            num++;

        cur_cell = getCellByCoords(x - 1, y + 1, m_grid.m_cells);
        if (cur_cell > 128)
            num++;

        cur_cell = getCellByCoords(x - 1, y, m_grid.m_cells);
        if (cur_cell > 128)
            num++;

        cur_cell = getCellByCoords(x - 1, y - 1, m_grid.m_cells);
        if (cur_cell > 128)
            num++;
    }
    return num;
}

EMSCRIPTEN_KEEPALIVE
std::vector<int> CaveGenerator::generate()
{
    fillRandom();
    smooth(m_smooth_iterations);
    // inspect();
    return m_grid.m_cells;
}

EMSCRIPTEN_BINDINGS(CaveGenerator_example)
{
    // emscripten::class_<CaveGenerator>::function<emscripten::internal::DeduceArgumentsTag, signed char *(CaveGenerator::*)()>;
    emscripten::class_<CaveGenerator>("CaveGenerator")
        .constructor()
        .function("generate", &CaveGenerator::generate)
        .function("setThreshold", &CaveGenerator::setThreshold)
        .function("getWidth", &CaveGenerator::getWidth)
        .function("setWidth", &CaveGenerator::setWidth)
        .function("getHeight", &CaveGenerator::getHeight)
        .function("setHeight", &CaveGenerator::setHeight)
        .function("setRandomSeed", &CaveGenerator::setRandomSeed)
        .function("setSmoothIterations", &CaveGenerator::setSmoothIterations);
    emscripten::register_vector<int>("vector<int>");
}
