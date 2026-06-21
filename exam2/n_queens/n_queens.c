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



/////
#include<unistd.h>
#include<stdio.h>
#include <stdlib.h>

void print_sub(int *sub,int size)
{
    int i = 0;
    while(i < size)
    {
        if(i)
            printf(" ");
        printf("%d",sub[i]);
        i++;
    }
    printf("\n");
}
void solve(int *arr,int *sub,int target,int n,int sum,int size,int index)
{
    if(index == n)
    {
        if(sum == target)
            print_sub(sub,size);
        return;
    }
    sub[size] = arr[index];
    solve(arr,sub,target,n,sum + arr[index],size + 1,index + 1);
    solve(arr,sub,target,n,sum,size,index + 1);
}

int main(int argc,char **argv)
{
    if(argc < 3)
        return 1;
    int n = argc -2;
    int target = atoi(argv[1]);
    int *arr = malloc(sizeof(int) * n);
    int *sub = malloc(sizeof(int) * n);
    if(!arr || !sub)
        return 1;
    int i = 0;
    while(i < n)
    {
        arr[i] = atoi(argv[i + 2]);
        i++;
    }
    solve(arr,sub,target,n,0,0,0);
    free(arr);
    free(sub);
}
