/*Welcome to my interpretation of GoL in C. I'm glad to hear that there aren't problems with my code, but they also can be*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
// set preprocessor const. equal size of GoL
#define SIZE 30

//clear cmd screen func.
int clear_screen()
{
    system("cls");
    return 0;
}
//counting neighbors func.
int grid_countneighbors(int grid[][SIZE], int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            int neighborX = x + i;
            int neighborY = y + j;
            // Skipping current cell
            if (i == 0 && j == 0)
            {
                continue;
            }
            // Check if neighbor is close to our cell
            if (neighborX >= 0 && neighborY >= 0 && neighborX < SIZE && neighborY < SIZE)
            {
                count += grid[neighborX][neighborY];
            }
        }
    }
    return count;
}

void grid_print(int grid[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            printf("%c ", grid[i][j] ? '*' : ' ');
        }
        printf("\n");
    }
}

void grid_update(int grid[][SIZE])
{
    int nextGrid[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int neighbors = grid_countneighbors(grid, i, j);
            // Apply game of life rules
            if (grid[i][j])
            {
                if (neighbors < 2 || neighbors > 3)
                {
                    nextGrid[i][j] = 0;
                }
                else
                {
                    nextGrid[i][j] = 1;
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    nextGrid[i][j] = 1;
                }
                else
                {
                    nextGrid[i][j] = 0;
                }
            }
        }
    }

    // Copy next grid to current grid
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            grid[i][j] = nextGrid[i][j];
        }
    }
}
//grid copy func.
void copy_grid(int dest[SIZE][SIZE], int src[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            dest[i][j] = src[i][j];
        }
    }
}
//compare grids func.
int compare_grid(int grid1[][SIZE], int grid2[][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (grid1[i][j] != grid2[i][j])
            {
                return 0; // = 0, if grid1 != grid 2
            }
        }
    }
    return 1; // = 1, if grid1 == grid2
}

int main()
{
    srand(time(NULL));
    int grid[SIZE][SIZE];
    int prev_grid[SIZE][SIZE];
    // Initialize grid randomly.
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            grid[i][j] = rand() % 2;
        }
    }
    copy_grid(prev_grid, grid);

    // Running GoF.
    while (1)
    {
        grid_print(grid);
        Sleep(50);
        clear_screen();
        grid_update(grid);
        if (compare_grid(prev_grid, grid))
        {
            break;
        }
        copy_grid(prev_grid, grid);
    }

    return 0;
}