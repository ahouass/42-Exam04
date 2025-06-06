
#include <stdio.h>
#include <stdlib.h>

int n;

void    init_board(int board[n][n])
{
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            board[i][j] = 0;
}

void    print_solution(int solution[])
{
    for (int i=0; i<n; i++)
        fprintf(stdout, "%d ", solution[i]);
    fprintf(stdout, "\n");
}

int is_valid(int row, int col, int board[n][n])
{
    int i, j;
    for (i=row-1; i>=0; i--)
        if (board[i][col] == 1)
            return (0);
    for (i=row-1, j=col-1; i>=0 && j>=0; i--, j--)
        if (board[i][j] == 1)
            return (0);
    for (i=row-1, j=col+1; i>=0 && j<n; i--, j++)
        if (board[i][j] == 1)
            return (0);
    return (1);
}

void    n_queens(int row, int board[n][n], int solution[])
{
    if (row == n)
    {
        print_solution(solution);
        return ;
    }
    for (int col=0; col<n; col++)
    {
        if (is_valid(row, col, board))
        {
            board[row][col] = 1;
            solution[row] = col;
            n_queens(row+1, board, solution);
            board[row][col] = 0;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || atoi(argv[1]) <= 0)
        return (1);
    n = atoi(argv[1]);
    int board[n][n];
    int solution[n];
    init_board(board);
    n_queens(0, board, solution);
    return (0);
}