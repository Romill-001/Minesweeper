#include "../headers/Cell.hpp"

Cell::Cell() {
    type = CellType::Empty;
    minesAround = 0;
    isRevealed = false;
    isFagged = false;
}