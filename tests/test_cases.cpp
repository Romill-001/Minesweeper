#include <gtest/gtest.h>
#include "../headers/Board.hpp"
#include "../headers/EventHandler.hpp"

TEST(HelloTest, BasicAssertions0)
{
    Board board;
    board.cells[0][0].type = CellType::Empty;
    board.step = 1;
    board.revealCell(0, 0);
    EXPECT_EQ(board.cells[0][0].isRevealed, true);
}
TEST(HelloTest, BasicAssertions1)
{
    Board board;
    board.step = 1;
    board.putFlag(0, 0);
    EXPECT_EQ(board.cells[0][0].type, CellType::Flag);
}
TEST(HelloTest, BasicAssertions2)
{
    Board board;
    board.switchMode();
    EXPECT_EQ(board.easyMode, false);
}
TEST(HelloTest, BasicAssertions2f)
{
    Board board;
    board.switchMode();
    board.switchMode();
    EXPECT_EQ(board.easyMode, true);
}
TEST(HelloTest, BasicAssertions3)
{
    Board board;
    board.foundMines = 10;
    board.restartBoardR();
    EXPECT_EQ(board.foundMines, 0);
}
TEST(HelloTest, BasicAssertions4)
{
    Board board;
    board.putFlag(0, 0);
    EXPECT_EQ(board.foundMines, 0);
}
TEST(HelloTest, BasicAssertions5)
{
    Board board;
    board.step = 1;
    board.putFlag(0, 0);
    EXPECT_EQ(board.foundMines, 1);
}
TEST(HelloTest, BasicAssertions6)
{   
    sf::RenderWindow window;
    Board board;
    board.cells[1][1].type = CellType::Mine;
    board.cells[1][1].isRevealed = true;
    board.draw(window);
    EXPECT_EQ(board.gameOverLose, true);
}




