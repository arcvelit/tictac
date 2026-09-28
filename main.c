#define TICTACDEF static inline
#include "tictactoe.h"

int main()
{
    // The only game state
    int board = set_turn(EMPTY_BOARD, PLAYER_X);
    // packed in an i32

    for(;;) {
        int square;

        printf("Player %c's turn: ", REPR[get_turn(board)]);
        if (scanf("%d", &square) != 1 || square < 0 || square > 8) {
            while ((square = getchar()) != '\n' && square != EOF) {}
            TRY_AGAIN:
            printf("Try again...\n");
            continue;
        }

        if (get_square(board, square) == NONE) {
            board = set_square(board, get_turn(board), square);
        } else {
            goto TRY_AGAIN;
        }

        print_board(board);

        if (outcome(board, get_turn(board), square)) {
            printf("Player %c wins!\n", REPR[get_turn(board)]);
            return 0;
        } else if (stale(board)) {
            printf("No winner...\n");
            return 0;
        }

        board = toggle_turn(board);
    }

    return 0;
}