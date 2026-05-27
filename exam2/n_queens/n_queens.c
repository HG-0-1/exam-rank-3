#include <stdlib.h>
#include <stdio.h>

int	is_safe(int *board, int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (board[i] == row)
			return (0);
		if (abs(board[i] - row) == abs(i - col))
			return (0);
		i++;
	}
	return (1);
}

void	print_sol(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("%d", board[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	solve(int *board, int n, int col)
{
	int	row;

	if (col == n)
	{
		print_sol(board, n);
		return ;
	}

	row = 0;
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			solve(board, n, col + 1);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int	n;
	int	*board;

	if (ac != 2)
		return (1);

	n = atoi(av[1]);
	if (n <= 0)
		return (1);

	board = calloc(n, sizeof(int));
	if (!board)
		return (1);

	solve(board, n, 0);

	free(board);
	return (0);
}
