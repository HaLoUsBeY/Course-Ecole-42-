
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int *queen_positions; 
int board_size; //(NxN)



int abs_val(int n) 
{
    return n < 0 ? -n : n;
}



void print_solution(void)
{
    for (int i = 0; i < board_size; i++) {
        fprintf(stdout, "%d", queen_positions[i]);
        if (i < board_size - 1)
            fprintf(stdout, " ");
    }
    fprintf(stdout, "\n");
}



int is_queen_safe(int y, int x)
{
    for (int prev_x = 0; prev_x < x; prev_x++) {
        if (queen_positions[prev_x] == y)
            return 0;
        if (abs_val(queen_positions[prev_x] - y) == abs_val(prev_x - x))
            return 0;
    }
    return 1;
}







void solve_n_queens(int x)
{
    if (x == board_size) {
        print_solution();
        return;
    }
    for (int y = 0; y < board_size; y++)
    {
        if (is_queen_safe(y, x))
        {
            queen_positions[x] = y;
            solve_n_queens(x + 1);
        }
    }
}





int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "\n", 1);
        return 0;
    }
    int n = atoi(argv[1]);

    board_size = n;
    queen_positions = malloc(sizeof(int) * board_size);
    if (!queen_positions)
        return 1;
    solve_n_queens(0);
    free(queen_positions);
    return 0;
}