#ifndef SUDOKU_H 
#define SUDOKU_H

const int MAX_FILENAME_LENGTH = 80; // global constant declared for max filename
																		// length for Q3 (as can't assign an array
																		// unlimited memory)

/* pre-supplied functions */
void load_board(const char* filename, char board[9][9]); void
display_board(const char board[9][9]);

/* Function that checks if a 9x9 sudoku board is complete or not Parameter char
 * board[9][9]: A character array representing a 9x9 sudoku board Function
 * returns true if board is complete, false if board is incomplete */
bool is_complete(char board[9][9]);


/* Helper function for the make_move function, that simply checks if the desired
 * co-ordinates for a given Sudoku move are valid (i.e. between A1 and I9)
 * Parameter const char position[2]: A character array containing the desired
 * co-ordinates Function returns true if the co-ordinates are in the valid
 * Sudoku board range, otherwise false */
bool check_coords(const char position[2]);

/* Helper function for the make_move function, that simply checks if the desired
 * digit for a given Sudoku move is valid (i.e. is a digit between 1 and 9).
 * Parameter char digit: The digit to be placed in a given Sudoku move.  Returns
 * true if the digit is valid, otherwise false */
bool check_digit(char digit);

/* Helper function for the make_move function, that checks if whether a desired
 * Sudoku move is valid according to the logical requirements of Sudoku (i.e.
 * digit does not feature in same mini 3x3 board, same column, or same row)
 * Parameters: a character array (position) contianing the co-ordinates of the
 * desired move; char digit containing the digit to be placed; char board[9][9]
 * which is the character array containing the Sudoku board in question.
 * Returns true if the digit placement is valid according to the Sudoku logical
 * rules, otherwise false */
bool check_digit_placement(const char position[2], char digit, char
		board[9][9]);

/* Function that combines the three above helper functions, checking if all are
 * true, and thus if the desired Sudoku move is a valid one. If the all three
 * above functions are true, the make_move function updates the Sudoku board to
 * reflect the move being made, and returns true. Otherwise the make_move
 * function returns false and does not update the board */
bool make_move(const char position[2], char digit, char board[9][9]);

/* Function that saves a 2D character array containg a Sudoku board, to a file
 * of a given name.  Parameter 1: A character array limited at a max length of
 * 80 characters, which is the string that contains the filename we are to save
 * the Sudoku board to.  Parameter 2: 9x9 character array representing the
 * Sudoku board, passed as a const char array, as we are not expecting the board
 * to undergo any changes during the saving process.  Function returns true if
 * the board was successfully saved to the file; otherwise false */ 
bool save_board(const char filename[MAX_FILENAME_LENGTH], const char
		board[9][9]);

/* Helper function for the second solve_board function at the bottom of this
 * header file. This first solve_board function only serves to: a) initialize an
 * int recursion_counter variable to 0 that can then be passed by reference into
 * the second solve_board function, and in doing so, serve as an effective
 * recursion counter that can be incremented with each recursive call to the
 * second solve_board function, but that resets to 0 between each Sudoku board.
 * b) start and end a timer to measure the time it takes for the second
 * solve_board function to finish executing.  c) call the second solve_board
 * function, to do the actual solving (in between starting and ending the
 * timer).  The function takes advantage of C++'s polymorphism; as all calls to
 * solve_board from main.cpp only have one parameter, so by defualt will be
 * routed through this helper solve_board function, that subsequently calls the
 * proper solve_board function.
 *
 * Parameter: The 9x9 character array representing the Sudoku board to be
 * solved.  Returns true is the second solve_board function returns true; false
 * if the second solve_board function returns false */ 
bool solve_board(char board[9][9]);

/* Solve_board function that takes a Sudoku board (9x9 character array) as
 * input, and solves the board by making use of the already defined make_move
 * function and its helper functions. The function also includes the
 * recursion_counter variable (explained above) passed by reference, to indicate
 * the level of complexity of the Sudoku board being solved.
 * 
 * Function returns true if board is able to be solved (and throughout the
 * solving process, updates the board to its solved state), false if board
 * cannot be solved. */
bool solve_board(char board[9][9], int &recursion_counter);

#endif
