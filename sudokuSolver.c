#include <stdio.h>

#define N 9 // size of the grid

// function to check if a given digit is available for a given cell
int isAvailable(int grid[N][N], int row, int col, int num) {
  int rowStart = (row / 3) * 3; // starting row index of the subgrid
  int colStart = (col / 3) * 3; // starting column index of the subgrid
  int i, j;

  // loop over the row, column, and subgrid to check for conflicts
  for (i = 0; i < N; i++) {
    if (grid[row][i] == num) return 0; // conflict in the row
    if (grid[i][col] == num) return 0; // conflict in the column
    if (grid[rowStart + (i % 3)][colStart + (i / 3)] == num) return 0; // conflict in the subgrid
  }

  return 1; // no conflict
}

// function to fill the sudoku grid using backtracking
int fillSudoku(int grid[N][N], int row, int col) {
  int i;

  // base case: if the index is at the end of the grid, the grid is solved 00
  if (row == N && col == 0) return 1;

  // base case: if the index is at the end of a row, move to the next row
  if (col == N) return fillSudoku(grid, row + 1, 0);

  // if the current cell is not empty, skip it and move to the next cell
  if (grid[row][col] != 0) return fillSudoku(grid, row, col + 1);

  // if the current cell is empty, try all possible digits
  for (i = 1; i <= N; i++) {
    // if the digit is available, fill the cell with it
    if (isAvailable(grid, row, col, i)) {
      grid[row][col] = i;

      // recursively try to fill the rest of the grid
      if (fillSudoku(grid, row, col + 1)) return 1; // solution found

      // if the recursive call fails, reset the cell to 0 and try the next digit
      grid[row][col] = 0;
    }
  }

  // if no digit works for the current cell, the grid is unsolvable
  return 0;
}

// function to print the sudoku grid in a nice format
void printSudoku(int grid[N][N]) {
  int i, j;

  // loop over the rows and columns
  for (i = 0; i < N; i++) {
    // print a horizontal separator every 3 rows
    if (i % 3 == 0) printf("+-----+-----+-----+\n");

    for (j = 0; j < N; j++) {
      // print a vertical separator every 3 columns
      if (j % 3 == 0) printf("|");

      // print the digit or a space for an empty cell
      if (grid[i][j] != 0) printf("%d", grid[i][j]);
      else printf(" ");

      // print a space after each digit
      printf(" ");
    }

    // print a vertical separator and a newline at the end of each row
    printf("|\n");
  }

  // print a horizontal separator at the end of the grid
  printf("+-----+-----+-----+\n");
}

// main function
int main() {
  int i, j;

  // a sample sudoku puzzle
  

  // initialize the sudoku grid with user input
  int grid[N][N];

  // prompt user to enter the sudoku puzzle row by row
  printf("Enter the sudoku puzzle (0 for empty cells, row-wise):\n");
  for (i = 0; i < 9; i++) {
    printf("Enter row %d : ", i + 1);
    for (j = 0; j < 9; j++) {
      scanf("%d", &grid[i][j]);
    }
  }

  // print the initial grid
  printf("Initial grid:\n");
  printSudoku(grid);

  // try to solve the grid
  if (fillSudoku(grid, 0, 0)) {
    // print the solved grid
    printf("Solved grid:\n");
    printSudoku(grid);
  } else {
    // print a message if the grid is unsolvable
    printf("No solution\n");
  }

  return 0;
}