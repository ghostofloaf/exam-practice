#include <iostream>
#include <cstdlib>
#include <ctime>

class Board {
private:
    int size;
    char** cells;

public:
    Board(int boardSize) : size(boardSize) {
        cells = new char*[size];
        for (int i = 0; i < size; ++i) {
            cells[i] = new char[size];
            for (int j = 0; j < size; ++j) {
                cells[i][j] = '-';
            }
        }
    }

    ~Board() {
        for (int i = 0; i < size; ++i) {
            delete[] cells[i];
        }
        delete[] cells;
    }

    void display() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << cells[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool isFull() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (cells[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

    bool isValidMove(int x, int y) const {
        return x >= 0 && x < size && y >= 0 && y < size && cells[x][y] == '-';
    }

    void placeMove(int x, int y, char player) {
        cells[x][y] = player;
    }

    void reset() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cells[i][j] = '-';
            }
        }
    }
};

class TicTacToe {
private:
    int size;
    Board* board;
    bool playerTurn;
    int numMoves;

public:
    TicTacToe(int boardSize) : size(boardSize), playerTurn(true), numMoves(0) {
        board = new Board(size);
    }

    ~TicTacToe() {
        delete board;
    }

    void display() const {
        board->display();
    }

    bool isFull() const {
        return board->isFull();
    }

    bool checkWin(char player) const {
        // Check rows and columns
        for (int i = 0; i < size; ++i) {
            int row_count = 0, col_count = 0;
            for (int j = 0; j < size; ++j) {
                if (board->isValidMove(i, j) && board->isValidMove(j, i)) {
                    if (board->isFull()) return true;
                }
            }
        }
        // Check diagonals
        int diag_count = 0, rev_diag_count = 0;
        for (int i = 0; i < size; ++i) {
            if (board->isValidMove(i, i)) diag_count++;
            if (board->isValidMove(i, size - 1 - i)) rev_diag_count++;
        }
        if (diag_count == size || rev_diag_count == size) return true;

        return false;
    }

    void playerMove(int x, int y) {
        if (board->isValidMove(x, y)) {
            board->placeMove(x, y, 'X');
            playerTurn = false;
            numMoves++;
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    void computerMove() {
        srand(time(0));
        int x, y;
        do {
            x = rand() % size;
            y = rand() % size;
        } while (!board->isValidMove(x, y));
        board->placeMove(x, y, 'O');
        playerTurn = true;
        numMoves++;
    }

    void play() {
        while (!isFull()) {
            std::cout << "Current Board:" << std::endl;
            display();

            if (playerTurn) {
                int x, y;
                std::cout << "Your turn (row column): ";
                std::cin >> x >> y;
                playerMove(x, y);
            } else {
                std::cout << "Computer's turn:" << std::endl;
                computerMove();
            }

            if (checkWin('X')) {
                std::cout << "Congratulations! You win!" << std::endl;
                break;
            } else if (checkWin('O')) {
                std::cout << "Sorry! Computer wins!" << std::endl;
                break;
            }
        }

        if (!checkWin('X') && !checkWin('O')) {
            std::cout << "It's a draw!" << std::endl;
        }

        // Clear the board for the next game
        board->reset();
    }
};

int main() {
    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Play the game" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int boardSize;
            std::cout << "Enter the size of the board (max 10): ";
            std::cin >> boardSize;

            TicTacToe game(boardSize);
            game.play();
        }
    } while (choice != 2);

    return 0;
}