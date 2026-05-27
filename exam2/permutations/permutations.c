#include <unistd.h>

int	len(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	write_str(char *s)
{
	write(1, s, len(s));
	write(1, "\n", 1);
}

void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (s[i] > s[j])
				swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
}

void	reverse(char *s, int start, int end)
{
	while (start < end)
	{
		swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

int	next_perm(char *s)
{
	int	i;
	int	j;

	i = len(s) - 2;
	while (i >= 0 && s[i] >= s[i + 1])
		i--;

	if (i < 0)
		return (0);

	j = len(s) - 1;
	while (s[j] <= s[i])
		j--;

	swap(&s[i], &s[j]);
	reverse(s, i + 1, len(s) - 1);

	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	sort(av[1]);

	write_str(av[1]);
	while (next_perm(av[1]))
		write_str(av[1]);

	return (0);
}
