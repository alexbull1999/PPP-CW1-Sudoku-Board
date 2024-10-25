#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"
#include <chrono> // library included for time measurement of recursive function

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

bool is_complete(char board[9][9]) 
{

	for (int row_num =0 ; row_num < 9; row_num++)
	{
		//Nested for loop to iterate through cols 1-9 of row 0, before onto row 1
		for (int col_num = 0 ; col_num < 9; col_num++) 
		{
			if (board[row_num][col_num] < '1' || board[row_num][col_num] > '9') 
			{
				//as soon as the first non-(1-9) space found, we can return false
				return false; 
			}
		}
	}

	return true; //only triggered if all rows/cols iterated through w/o empties
}

/* helper function to check if co-ords are permissible */
bool check_coords(const char position[2])
{
	if (position[0] < 'A' || position[0] > 'I') //Checking if row is between A-I
	{
		return false;
	}

	if (position[1] < '1' || position[1] > '9') //Checking if col is between 1-9
	{
		return false;
	}

	return true; //For code to reach this point, co-ordinates must be valid
	
}

/* helper function to check if digit is permissible (i.e. 1-9) */
bool check_digit(char digit)
{
	if (digit >= '1' && digit <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* helper function to check if digit placement is permissible with sudoku logic */
bool check_digit_placement(const char position[2], char digit, char board[9][9])
{
	char row_index = position[0];
	char col_index = position[1];
	//Using ASCII values to rebase row_num to 0-8 corresponding to row index of A-I
	int row_num = static_cast<int>(row_index) - 'A'; 
	//Using ASCII values to rebase col_num to 0-8 corresponding to col index of 1-9
	int col_num = static_cast<int>(col_index) - '1'; 	
	
	if (board[row_num][col_num] >= '1' && board[row_num][col_num] <= '9')
	{
		return false; //if a digit is already in the cell, do not want to overwrite it
	}

	//Iterate through all cols for desired row, to check if digit already appears
	for (int col_checker = 0; col_checker < 9; col_checker++) 
	{
		if (board[row_num][col_checker] == digit)
		{
			return false;
		}
	}

	//Iterate through all rows for desired column to check if digit already appears
	for (int row_checker = 0; row_checker < 9; row_checker++) 
	{
		if (board[row_checker][col_num] == digit)
		{
			return false;
		}
	}

	/* We still need to check whether digit already present in the 
	 * given 3x3 mini square, as if so that is also invalid */

	int mini_sudoku_row_start;
	int mini_sudoku_col_start;

	if (row_num <= 2)
	{
		mini_sudoku_row_start = 0;
	}
	else if (row_num > 2 && row_num <= 5)
	{
		mini_sudoku_row_start = 3;
	}
	else
	{
		mini_sudoku_row_start = 6;
	}

	if (col_num <= 2)
	{
		mini_sudoku_col_start = 0;
	}
	else if (col_num > 2 && col_num <= 5)
	{
		mini_sudoku_col_start = 3;
	}
	else
	{
		mini_sudoku_col_start = 6;
	}

	/* traversing through all squares in the mini 3x3 sudoku to 
	 * make sure the digit doesn't already exist within it */
	for (int row_checker = mini_sudoku_row_start; 
			row_checker < (mini_sudoku_row_start + 3); row_checker++) 	
	{
		for (int col_checker = mini_sudoku_col_start; 
				col_checker < (mini_sudoku_col_start + 3); col_checker++)
		{
			if (board[row_checker][col_checker] == digit)
			{
				return false;
			}
		}
	}

	/* If the code has made it to the line above without returning false, 
	 * it means the digit placement is valid, as:
	 * a) the digit does not already appear anywhere in desired insertion row/col
	 * b) the digit does not already appear anywhere in the 3x3 mini sudoku */

	return true; 

}

/* Complete make_move function, utilising helper functions */

bool make_move(const char position[2], char digit, char board[9][9])
{
	char row_index = position[0];
	char col_index = position[1];
	//Using ASCII values to reset row_num to 0 if row A
	int row_num = (static_cast<int>(row_index) - 'A'); 
	//Using ASCII values to reset col_num to 0 if col 1
	int col_num = (static_cast<int>(col_index) - '1'); 

	if (check_coords(position) && check_digit(digit) 
			&& check_digit_placement(position, digit, board))
	{
		board[row_num][col_num] = digit;
		return true;
	}
	else
	{
		return false;
	}
}

/* save_board function */

//MAX_FILENAME_LENGTH is a global constant declared in the sudoku.h header file
bool save_board(const char filename[MAX_FILENAME_LENGTH], const char board[9][9]) 
{
	ofstream out_stream;
	out_stream.open(filename);
	if (out_stream.fail())
	{
		return false;
	}

	for (int row_counter = 0; row_counter < 9; row_counter++)
	{
		//Allowing col_counter to reach 9, so we know when to write a newline
		for (int col_counter = 0; col_counter <= 9; col_counter++) 
		{
			if (col_counter < 9)
			{
				out_stream.put(board[row_counter][col_counter]);
			}
			else if (col_counter == 9)
			{
				out_stream.put('\n');
			}
		}
	}

	out_stream.close();
	return true;
}

/* Internal helper solve_board function with only one parameter, so it works 
 * with calls of solve_board from main.cpp with only one parameter. 
 * Sets a recursion counter, that is passed by reference into the 
 * proper solve_board function. (See header file for more details) */

bool solve_board(char board[9][9])
{
	// initialising recursion counter to 0, so resets with every new call from main
	int recursion_counter = 0; 
	auto start{chrono::high_resolution_clock::now()};
	bool result = solve_board(board, recursion_counter);
	auto end{chrono::high_resolution_clock::now()};
	chrono::duration<double, milli> recursion_seconds{end-start};
	cout << "Total time taken to run solve_board function solve is: ";
	cout << recursion_seconds.count() << " ms" << endl;
	return result;
}


/* solve_board main function */

//using the parameter passed by reference as a recursion counter 
bool solve_board(char board[9][9], int &recursion_counter) 
{

	if (is_complete(board)) //check base case to start with
	{	
		cout << "Final recursion counter stands at: " << recursion_counter << "\n"; 
		return true;
	}

	for (int row_counter = 0 ; row_counter < 9 ; row_counter++)
	{
		for (int col_counter = 0 ; col_counter < 9 ; col_counter++)
		{
			if (board[row_counter][col_counter] >= '1' 
					&& board[row_counter][col_counter] <= '9') 
			{
					//If a square is already complete, we can skip it 
				continue;
			}

			// iterate through all digits 1-9 until valid move found 
			for (char digit = '1'; digit <= '9'; digit++) 
			{
				// Converting row_counter into co-ordinate letter form
				char row_letter = static_cast<char>(row_counter) + 'A'; 
				// Conveting col_counter into co-ordinate number form
				char col_char = static_cast<char>(col_counter) + '1'; 
				char coords[2];
				coords[0] = row_letter;
				coords[1] = col_char;

				if (make_move(coords, digit, board)) // check if move is valid
				{
					recursion_counter++; //if valid, increment recursion counter 
					if (solve_board(board, recursion_counter)) //board parameter now updated
					{
						return true; //if solve_board true cascade it back
					}
					else //i.e. solve_board can't complete, so need to reset the cell to empty
					{
						board[row_counter][col_counter] = '.';
					}
				}
			}
			
			/* This means we have made it out of the for loop, with no digit 
			 * representing a valid move. So we return a false value from our
			 * current stack frame to the previous call of solve_board, so 
			 * that it resets the previous move made back to a null value. */

			return false; 		
			
		}
	}

	/* we have now left the for loops and the board has still not been caught by 
	 * the is_complete function in line 280.This means the board is unsolvable 
	 * and hence we should return false */

	return false;

}
	

