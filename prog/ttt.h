#pragma once
#include <iostream>
#include <vector>

class TicTacToe {
public:
    TicTacToe();
    TicTacToe(const int size, const int winLen);
    TicTacToe(const TicTacToe& other);
    ~TicTacToe(){};
    int getSize() const {
        return this->size;
    }
    int getWinLen() const {
        return this->winLen;
    }
    char getCurrentPlayer() const;
    bool canPlace(const int row, const int col) const;
    bool move(const int row, const int col);
    char checkWinner() const;
    char operator[](const int index) const;
    char& operator[](const int index);
    static void printBoard(const TicTacToe& game);
    TicTacToe& operator=(const TicTacToe& other);
    bool operator==(const TicTacToe& other) const;
    bool operator!=(const TicTacToe& other) const;
    friend std::ostream& operator<<(std::ostream& os, const TicTacToe& game);
    friend std::istream& operator>>(std::istream& is, TicTacToe& game);
private:
    int size = 3;
    int winLen = 3;
    std::vector<char> cells;
    bool hasLine(const char player) const;
};
