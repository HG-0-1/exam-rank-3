#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *set, int *used, int size)
{
	int	first;
	int	i;

	first = 1;
	i = 0;
	while (i < size)
	{
		if (used[i])
		{
			if (!first)
				printf(" ");
			printf("%d", set[i]);
			first = 0;
		}
		i++;
	}
	printf("\n");
}

void	backtrack(int *set, int *used, int size, int target, int idx, int sum)
{
	if (idx == size)
	{
		if (sum == target)
			print_subset(set, used, size);
		return ;
	}

	used[idx] = 0;
	backtrack(set, used, size, target, idx + 1, sum);

	used[idx] = 1;
	backtrack(set, used, size, target, idx + 1, sum + set[idx]);
}

int	main(int ac, char **av)
{
	int	target;
	int	size;
	int	*set;
	int	*used;
	int	i;

	if (ac < 3)
		return (1);

	target = atoi(av[1]);
	size = ac - 2;

	set = malloc(sizeof(int) * size);
	used = calloc(size, sizeof(int));
	if (!set || !used)
		return (1);

	i = 0;
	while (i < size)
	{
		set[i] = atoi(av[i + 2]);
		i++;
	}

	backtrack(set, used, size, target, 0, 0);

	free(set);
	free(used);
	return (0);
}
