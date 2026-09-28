# tictac
Tic-tac-toe game packed in an int

```c
// The only game state
int board = set_turn(EMPTY_BOARD, PLAYER_X);
// packed in an i32
```

## Packing
* The two most significant bits hold the turn `{ X: 01, O: 11 }`
* The 18 least significant bits hold the squares
  * Each square is represented by a two-bit pair corresponding to the player
