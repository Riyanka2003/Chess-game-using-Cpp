#include <iostream>
#include <vector>
#include <string>

enum Piece { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum Color { NONE, WHITE, BLACK };

struct Square {
    Piece piece;
    Color color;
};

class Chess {
public:
    /// @brief 
    Chess() {
        board.resize(8, std::vector<Square>(8, {EMPTY, NONE}));
        setupBoard();
    }

    void printBoard() const {
        for (int row = 7; row >= 0; --row) {
            for (int col = 0; col < 8; ++col) {
                char pieceChar = getPieceChar(board[row][col]);
                std::cout << pieceChar << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool movePiece(int fromRow, int fromCol, int toRow, int toCol) {
        if (isValidMove(fromRow, fromCol, toRow, toCol)) {
            std::swap(board[toRow][toCol], board[fromRow][fromCol]);
            board[fromRow][fromCol] = {EMPTY, NONE};
            return true;
        }
        return false;
    }

private:
    std::vector<std::vector<Square>> board;

    void setupBoard() {
        // Setup pawns
        for (int col = 0; col < 8; ++col) {
            board[1][col] = {PAWN, WHITE};
            board[6][col] = {PAWN, BLACK};
        }
        // Setup rooks
        board[0][0] = board[0][7] = {ROOK, WHITE};
        board[7][0] = board[7][7] = {ROOK, BLACK};
        // Setup knights
        board[0][1] = board[0][6] = {KNIGHT, WHITE};
        board[7][1] = board[7][6] = {KNIGHT, BLACK};
        // Setup bishops
        board[0][2] = board[0][5] = {BISHOP, WHITE};
        board[7][2] = board[7][5] = {BISHOP, BLACK};
        // Setup queens
        board[0][3] = {QUEEN, WHITE};
        board[7][3] = {QUEEN, BLACK};
        // Setup kings
        board[0][4] = {KING, WHITE};
        board[7][4] = {KING, BLACK};
    }

    char getPieceChar(const Square& square) const {
        switch (square.piece) {
            case PAWN: return square.color == WHITE ? 'P' : 'p';
            case ROOK: return square.color == WHITE ? 'R' : 'r';
            case KNIGHT: return square.color == WHITE ? 'N' : 'n';
            case BISHOP: return square.color == WHITE ? 'B' : 'b';
            case QUEEN: return square.color == WHITE ? 'Q' : 'q';
            case KING: return square.color == WHITE ? 'K' : 'k';
            default: return '.';
        }
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const {
        if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            return false;
        }
        const Square& fromSquare = board[fromRow][fromCol];
        const Square& toSquare = board[toRow][toCol];
        if (fromSquare.color == NONE || fromSquare.color == toSquare.color) {
            return false;
        }
        // Add more detailed move validation logic here (based on piece type, board state, etc.)
        return true;
    }
};

int main() {
    Chess chess;
    chess.printBoard();

    std::string from, to;
    while (true) {
        std::cout << "Enter move (e.g. e2 e4): ";
        std::cin >> from >> to;
        if (from.size() != 2 || to.size() != 2) {
            std::cout << "Invalid input format!" << std::endl;
            continue;
        }

        int fromCol = from[0] - 'a';
        int fromRow = from[1] - '1';
        int toCol = to[0] - 'a';
        int toRow = to[1] - '1';

        if (chess.movePiece(fromRow, fromCol, toRow, toCol)) {
            chess.printBoard();
        } else {
            std::cout << "Invalid move!" << std::endl;
        }
    }

    return 0;
}
