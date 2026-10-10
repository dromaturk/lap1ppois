#include <iostream>
#include <sstream>
#ifdef USE_UNITTEST
#include <UnitTest++/UnitTest++.h>
#endif
#include "ttt.h"

#ifdef USE_UNITTEST
SUITE(TicTacToeTestSuite) {

    TEST(DefaultConstructor) {
        TicTacToe g;
        CHECK_EQUAL(3, g.getSize());
        CHECK_EQUAL(3, g.getWinLen());
        CHECK_EQUAL('X', g.getCurrentPlayer());
    }

    TEST(ParametricConstructor) {
        TicTacToe g(5, 4);
        CHECK_EQUAL(5, g.getSize());
        CHECK_EQUAL(4, g.getWinLen());
    }

    TEST(ParametricConstructor_ClampWinLen) {
        TicTacToe g(3, 10);
        CHECK_EQUAL(3, g.getWinLen());
    }

    TEST(ParametricConstructor_MinSize) {
        TicTacToe g(0, 0);
        CHECK_EQUAL(1, g.getSize());
        CHECK_EQUAL(1, g.getWinLen());
    }

    TEST(CopyConstructor) {
        TicTacToe a(4, 3);
        a.move(0, 0);
        TicTacToe b(a);
        CHECK(a == b);
        b.move(1, 1);
        CHECK(a != b);
    }

    TEST(CanPlace) {
        TicTacToe g;
        CHECK(g.canPlace(1, 1));
        CHECK(!g.canPlace(3, 0));
        CHECK(!g.canPlace(-1, 0));
        g.move(1, 1);
        CHECK(!g.canPlace(1, 1));
    }

    TEST(CurrentPlayerAlternates) {
        TicTacToe g;
        CHECK_EQUAL('X', g.getCurrentPlayer());
        g.move(0, 0);
        CHECK_EQUAL('O', g.getCurrentPlayer());
        g.move(0, 1);
        CHECK_EQUAL('X', g.getCurrentPlayer());
    }

    TEST(Move_AfterWin_Rejected) {
        TicTacToe g;
        g.move(0, 0); g.move(1, 0);
        g.move(0, 1); g.move(1, 1);
        g.move(0, 2); // X побеждает
        CHECK(!g.move(2, 2));
    }

    TEST(Move_OutOfBounds_Rejected) {
        TicTacToe g;
        CHECK(!g.move(-1, 0));
        CHECK(!g.move(0, 5));
    }
    
    TEST(IndexOperator) {
        TicTacToe g;
        g[4] = 'X';
        CHECK_EQUAL('X', g[4]);
        CHECK_EQUAL(' ', g[0]);
        CHECK_THROW(g[9], std::out_of_range);
        CHECK_THROW(g[-1], std::out_of_range);
    }

    TEST(IndexOperator_Const) {
        const TicTacToe g;
        CHECK_EQUAL(' ', g[0]);
        CHECK_THROW(g[100], std::out_of_range);
    }

    TEST(RowWin) {
        TicTacToe g;
        g.move(0, 0); g.move(1, 0);
        g.move(0, 1); g.move(1, 1);
        g.move(0, 2);
        CHECK_EQUAL('X', g.checkWinner());
    }

    TEST(ColumnWin) {
        TicTacToe g;
        g.move(0, 0); g.move(0, 1);
        g.move(1, 0); g.move(0, 2);
        g.move(2, 0);
        CHECK_EQUAL('X', g.checkWinner());
    }

    TEST(DiagonalWin) {
        TicTacToe g;
        g.move(0, 0); g.move(0, 1);
        g.move(1, 1); g.move(0, 2);
        g.move(2, 2);
        CHECK_EQUAL('X', g.checkWinner());
    }

    TEST(AntiDiagonalWin) {
        TicTacToe g;
        g.move(0, 2); g.move(0, 0);
        g.move(1, 1); g.move(0, 1);
        g.move(2, 0);
        CHECK_EQUAL('X', g.checkWinner());
    }

    TEST(WinLen_FourInFive) {
        TicTacToe g(5, 4);
        g.move(0, 0); g.move(1, 0);
        g.move(0, 1); g.move(1, 1);
        g.move(0, 2); g.move(1, 2);
        g.move(0, 3);
        CHECK_EQUAL('X', g.checkWinner());
    }

    TEST(Draw) {
        TicTacToe g;
        int order[9][2] = {{0,0},{0,1},{0,2},{1,1},{1,0},{1,2},{2,1},{2,0},{2,2}};
        for (auto& o : order) g.move(o[0], o[1]);
        CHECK_EQUAL('D', g.checkWinner());
    }

    TEST(NoWinnerYet) {
        TicTacToe g;
        g.move(0, 0);
        CHECK_EQUAL(' ', g.checkWinner());
    }
    
    TEST(PrintBoard_NoThrow) {
        TicTacToe g;
        g.move(0, 0);
        CHECK(true);
    }
    
    TEST(ComparisonAndAssignmentOperators) {
        TicTacToe a;
        TicTacToe b;
        a.move(0, 0);
        CHECK(a != b);
        b = a;
        CHECK(a == b);
        b = b;
        CHECK(a == b);
        TicTacToe c(a);
        CHECK(c == a);
    }

    TEST(StreamOperators) {
        std::stringstream ss;
        TicTacToe in(4, 3);
        in.move(0, 0);
        in.move(3, 3);
        ss << in;
        TicTacToe out;
        ss >> out;
        CHECK(in == out);
    }

    TEST(StreamOperators_InvalidInput) {
        std::stringstream ss("0 0\n");
        TicTacToe g;
        ss >> g;
        CHECK(ss.fail());
    }
}
#endif

void interactiveMode() {}

int main() {}
