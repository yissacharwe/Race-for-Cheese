#pragma once

struct Location
{
    Location() = default;
    Location(int row, int col) : row(row), col(col) {}
    int row;
    int col;
};
