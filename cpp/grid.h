#ifndef GRID_H
#define GRID_H

#include <vector>
class Grid
{
public:
    Grid();
    Grid(unsigned int resx, unsigned int resy);
    ~Grid();

    Grid(const Grid &other)
    {
        m_cells = other.m_cells;
        m_resx = other.m_resx;
        m_resy = other.m_resy;
    }

    void init();
    void setResX(unsigned int value) { m_resx = value; }
    void setResY(unsigned int value) { m_resy = value; }

    void zeros();

private:
public:
    unsigned int m_resx;
    unsigned int m_resy;

    std::vector<int> m_cells;
};
#endif /* GRID_H */