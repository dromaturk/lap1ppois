#include "ttt.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

TicTacToe::TicTacToe() : cells(9, ' ') {}

TicTacToe::TicTacToe(const int size, const int winLen) {
    this->size = max(size, 1);
    this->winLen = min(max(winLen, 1), this->size);
    this->cells.assign(this->size * this->size, ' ');
}

TicTacToe::TicTacToe(const TicTacToe& other) {
    this->size = other.size;
    this->winLen = other.winLen;
    this->cells = other.cells;
}

char TicTacToe::getCurrentPlayer() const {
    int x = count(cells.begin(), cells.end(), 'X');
    int o = count(cells.begin(), cells.end(), 'O');
    return x == o ? 'X' : 'O';
}

bool TicTacToe::canPlace(const int row, const int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) return false;
    return cells[row * size + col] == ' ';
}

bool TicTacToe::move(const int row, const int col) {
    if (checkWinner() != ' ' || !canPlace(row, col)) return false;
    cells[row * size + col] = getCurrentPlayer();
    return true;
}

bool TicTacToe::hasLine(const char player) const {
    const int dr[4] = {0, 1, 1, 1};
    const int dc[4] = {1, 0, 1, -1};
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            for (int d = 0; d < 4; d++) {
                int k = 0;
                while (k < winLen) {
                    int nr = r + dr[d] * k;
                    int nc = c + dc[d] * k;
                    if (nr < 0 || nr >= size || nc < 0 || nc >= size) break;
                    if (cells[nr * size + nc] != player) break;
                    k++;
                }
                if (k == winLen) return true;
            }
        }
    }
    return false;
}

char TicTacToe::checkWinner() const {
    if (hasLine('X')) return 'X';
    if (hasLine('O')) return 'O';
    if (find(cells.begin(), cells.end(), ' ') == cells.end()) return 'D';
    return ' ';
}

char TicTacToe::operator[](const int index) const {
    if (index < 0 || index >= size * size) throw out_of_range("Index out of range");
    return cells[index];
}

char& TicTacToe::operator[](const int index) {
    if (index < 0 || index >= size * size) throw out_of_range("Index out of range");
    return cells[index];
}

void TicTacToe::printBoard(const TicTacToe& game) {
    for (int r = 0; r < game.size; r++) {
        for (int c = 0; c < game.size; c++) {
            char cell = game.cells[r * game.size + c];
            cout << (cell == ' ' ? '.' : cell) << " ";
        }
        cout << "\n";
    }
}

TicTacToe& TicTacToe::operator=(const TicTacToe& other) {
    if (this == &other) return *this;
    this->size = other.size;
    this->winLen = other.winLen;
    this->cells = other.cells;
    return *this;
}

bool TicTacToe::operator==(const TicTacToe& other) const {
    return size == other.size
        && winLen == other.winLen
        && cells == other.cells;
}

bool TicTacToe::operator!=(const TicTacToe& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, const TicTacToe& game) {
    os << game.size << " " << game.winLen << "\n";
    for (int r = 0; r < game.size; r++) {
        for (int c = 0; c < game.size; c++) {
            char cell = game.cells[r * game.size + c];
            os << (cell == ' ' ? '.' : cell) << (c + 1 < game.size ? " " : "");
        }
        os << "\n";
    }
    return os;
}

istream& operator>>(istream& is, TicTacToe& game) {
    int size, winLen;
    if (!(is >> size >> winLen) || size < 1 || size > 100) {
        is.setstate(ios::failbit);
        return is;
    }
    TicTacToe temp(size, winLen);
    for (int i = 0; i < size * size; i++) {
        char c;
        if (!(is >> c) || (c != 'X' && c != 'O' && c != '.')) {
            is.setstate(ios::failbit);
            return is;
        }
        temp.cells[i] = c == '.' ? ' ' : c;
    }
    game = temp;
    return is;
}
