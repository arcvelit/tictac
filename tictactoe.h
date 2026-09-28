#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdint.h>

typedef enum {
    TOP_LEFT, TOP_MID, TOP_RIGHT,
    MID_LEFT, MID_MID, MID_RIGHT,
    BOT_LEFT, BOT_MID, BOT_RIGHT,
} square;

typedef enum {
    NONE,
    PLAYER_X,
    PLAYER_O,
} player;


#define b(x) (1 << (x)*2)
#define EMPTY_BOARD 0

#define PACKED_ROW_1 (b(TOP_LEFT) | b(TOP_MID)  | b(TOP_RIGHT))
#define PACKED_COL_1 (b(BOT_LEFT) | b(MID_LEFT) | b(TOP_LEFT) )

#define PACKED_DIAG_DESC (b(TOP_LEFT) | b(MID_MID) | b(BOT_RIGHT))
#define PACKED_DIAG_ASC  (b(BOT_LEFT) | b(MID_MID) | b(TOP_RIGHT))

const char REPR[3] = {' ', 'X', 'O'};

TICTACDEF int check(int board, int line) {
    return (board & line) == line;
}

TICTACDEF int set_square(int board, player p, square s) {
    return board | (1 << (p - 1) << s*2 );
}

TICTACDEF player get_square(int board, square s) {
    return (board >> s * 2) & 0b11;
}

#define TURN_SHIFT (8 * sizeof(int) - 2)
#define TURN_MASK  (0b11 << TURN_SHIFT)

TICTACDEF player get_turn(int board) {
    return (board >> TURN_SHIFT) & 0b11;
}

TICTACDEF int set_turn(int board, player p) {
    return (board & ~TURN_MASK) | (p << TURN_SHIFT);
}

TICTACDEF int toggle_turn(int board) {
    return board ^ TURN_MASK;
}

TICTACDEF int outcome(int board, player p, square s) {
    const int off = p - 1;
    const int col = s % 3;
    const int row = s / 3;
    return check(board, PACKED_ROW_1 << off << 6 * row) ||
           check(board, PACKED_COL_1 << off << 2 * col) ||
           check(board, PACKED_DIAG_DESC << off) ||
           check(board, PACKED_DIAG_ASC  << off);
}

void print_board(int board) {
    printf("Tic Tac Toe");
    for (int s = 0; s < 9; s++) {
        if (s % 3 == 0) {
            printf("\n");
        }
        switch (get_square(board, s)) {
            case NONE:     { printf("#"); break; }
            case PLAYER_O: { printf("O"); break; }
            case PLAYER_X: { printf("X"); break; }
        }
    }
    printf("\n");
}

int stale(int board) {
    for (int s = 0; s < 9; s++) {
        if (get_square(board, s) == NONE) {
            return 0;
        }
    }
    return 1;
}

#endif // TICTACTOE_H