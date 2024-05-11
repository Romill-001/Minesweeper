#ifndef CELL_HPP
#define CELL_HPP

enum class CellType {
    Empty,
    Mine,
    Flag
};

class Cell
{
public:
    CellType type;
    bool isRevealed;
    int minesAround;
    Cell();
};

#endif //CELL_HPP