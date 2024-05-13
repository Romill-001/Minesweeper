#include <gtest/gtest.h>
#include "../headers/Board.hpp"
#include "../headers/EventHandler.hpp"

TEST(HelloTest, BasicAssertions0)
{
    Board board;
    std::vector<std::vector<Cell>> tmp = board.getCells();
    tmp[0][0].type = CellType::Empty;
    board.setCells(tmp);
    board.setStep(1);
    board.revealCell(0, 0);
    EXPECT_EQ(board.getCells()[0][0].isRevealed, true);
}
TEST(HelloTest, BasicAssertions1)
{
    Board board;
    board.setStep(1);
    board.putFlag(0, 0);
    EXPECT_EQ(board.getCells()[0][0].type, CellType::Flag);
}
TEST(HelloTest, BasicAssertions2)
{
    Board board;
    board.switchMode();
    EXPECT_EQ(board.getMode(), false);
}
TEST(HelloTest, BasicAssertions2f)
{
    Board board;
    board.switchMode();
    board.switchMode();
    EXPECT_EQ(board.getMode(), true);
}
TEST(HelloTest, BasicAssertions3)
{
    Board board;
    board.setFoundMines(10);
    board.restartBoardR();
    EXPECT_EQ(board.getFoundMines(), 0);
}
TEST(HelloTest, BasicAssertions4)
{
    Board board;
    board.putFlag(0, 0);
    EXPECT_EQ(board.getFoundMines(), 0);
}
TEST(HelloTest, BasicAssertions5)
{
    Board board;
    board.setStep(1);
    board.putFlag(0, 0);
    EXPECT_EQ(board.getFoundMines(), 1);
}
TEST(HelloTest, BasicAssertions6)
{   
    sf::RenderWindow window;
    Board board;
    std::vector<std::vector<Cell>> tmp = board.getCells();
    tmp[1][1].type = CellType::Mine;
    tmp[1][1].isRevealed = true;
    board.setCells(tmp);
    board.draw(window);
    EXPECT_EQ(board.getGameOverLose(), true);
}




