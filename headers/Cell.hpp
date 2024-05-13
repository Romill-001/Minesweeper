#ifndef CELL_HPP
#define CELL_HPP

enum class CellType {
    Empty,
    Mine
};

class Cell {
public:
    Cell();
    CellType type;
    bool isRevealed;
    int minesAround;
    bool isFagged;
};

#endif //CELL_HPP