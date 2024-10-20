#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  
  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";



  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // write more test
	// this test below should be valid
	
	cout << "Putting '7' into A1 is ";
	if (!make_move("A1", '7', board)) {
		cout << "NOT ";
	}
	cout << "a valid move. The board is:\n";
	display_board(board);

	//this test below should be valid
	
	cout << "Putting '3' into B3 is ";
	if (!make_move("B3", '3', board)) {
		cout << "NOT ";
	}
	cout << "a valid move. The board is:\n";
	display_board(board);

	// this test below should be valid
	
	cout << "Putting '6' into I9 is ";
	if (!make_move("I9", '6', board)) {
		cout << "NOT ";
	}
	cout << "a valid move. The board is:\n";
	display_board(board);

	// this test should be invalid
	
	cout << "Putting '1' into A1 is ";
	if (!make_move("A1", '1', board)) {
		cout << "NOT ";
	}
	cout << "a valid move. The board is:\n";
	display_board(board);

	


  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

	
	load_board("easy-solution.dat", board);
	if (save_board("easy-solution-copy.dat", board)) {
		cout << "Save board to 'easy-solution-copy.dat' successful.\n";
	} else {
		cout << "Save board failed.\n";
	}
	cout << '\n';


  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  } 
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

	// testing on a pre-filled board to see if it throws and error
	
	load_board("easy-solution.dat", board);
	if (solve_board(board)) {
		cout << "The 'easy-solution' board has a solution:\n";
		display_board(board);
	} else {
		cout << "A solution cannot be found.\n";
	}
	cout << '\n';
  

  cout << "=================== Question 5 ===================\n\n";

  load_board("mystery1.dat", board);
	if (solve_board(board)) {
		cout << "The 'mystery1' board has a solution:\n";
		display_board(board);
	} else {
		cout << "A solution cannot be found.\n";
	}
	cout << '\n';

	load_board("mystery2.dat", board);
	if (solve_board(board)) {
		cout << "The 'mystery2' board has a solution:\n";
		display_board(board);
	} else {
		cout << "A solution cannot be found.\n";
	}
	cout << '\n';

	load_board("mystery3.dat", board);
	if (solve_board(board)) {
		cout << "The 'mystery3' board has a solution:\n";
		display_board(board);
	} else {
		cout << "A solution cannot be found.\n";
	}
	cout << '\n';

  return 0;
}
