#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct s_city
{
	float	x;
	float	y;
}	t_city;

float	dist(t_city a, t_city b)
{
	float	dx;
	float	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	return (sqrtf(dx * dx + dy * dy));
}

void	tsp(t_city *cities, int n, int *used,
		int depth, int current, float cost, float *best)
{
	int	i;

	if (cost >= *best)
		return ;
	if (depth == n)
	{
		cost += dist(cities[current], cities[0]);
		if (cost < *best)
			*best = cost;
		return ;
	}
	i = 0;
	while (i < n)
	{
		if (!used[i])
		{
			used[i] = 1;
			tsp(cities, n, used, depth + 1,
				i,
				cost + dist(cities[current], cities[i]),
				best);
			used[i] = 0;
		}
		i++;
	}
}

int	main(void)
{
	t_city	*cities;
	t_city	*tmp;
	int		cap;
	int		n;
	int		*used;
	float	best;

	cap = 16;
	n = 0;
	cities = malloc(sizeof(t_city) * cap);
	if (!cities)
		return (1);
	while (scanf("%f, %f", &cities[n].x, &cities[n].y) == 2)
	{
		n++;
		if (n >= cap)
		{
			cap *= 2;
			tmp = realloc(cities, sizeof(t_city) * cap);
			if (!tmp)
				return (1);
			cities = tmp;
		}
	}
	if (n == 0)
		return (1);
	used = calloc(n, sizeof(int));
	if (!used)
		return (1);
	best = FLT_MAX;
	used[0] = 1;
	tsp(cities, n, used, 1, 0, 0.0f, &best);
	printf("%.2f\n", best);
	free(cities);
	free(used);
	return (0);
}
