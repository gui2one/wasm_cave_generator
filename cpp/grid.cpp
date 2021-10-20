#include "grid.h"

Grid::Grid()
{
}
Grid::Grid(unsigned int resx, unsigned int resy)
{
    m_resx = resx;
    m_resy = resy;
}
Grid::~Grid()
{
}

void Grid::init()
{
    m_cells.clear();
    m_cells.reserve(m_resx * m_resy);
    for (int y = 0; y < m_resy; y++)
    {
        for (int x = 0; x < m_resx; x++)
        {
            m_cells.emplace_back(0);
        }
    }
}

void Grid::zeros()
{
    std::fill(m_cells.begin(), m_cells.end(), 0);
}