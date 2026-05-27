#include <unistd.h>

int	len(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	valid(char *s)
{
	int	i = 0;
	int	open = 0;

	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			open--;
			if (open < 0)
				return (0);
		}
		i++;
	}
	return (open == 0);
}

void	print(char *s)
{
	int	i = 0;

	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	solve(char *s, int idx, int rem)
{
	int	i;
	char	tmp;

	if (rem == 0)
	{
		if (valid(s))
			print(s);
		return ;
	}

	i = idx;
	while (s[i])
	{
		if (s[i] == '(' || s[i] == ')')
		{
			tmp = s[i];
			s[i] = ' ';
			solve(s, i + 1, rem - 1);
			s[i] = tmp;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	open;
	int	close;

	if (ac != 2)
		return (1);

	open = 0;
	close = 0;
	i = 0;

	while (av[1][i])
	{
		if (av[1][i] == '(')
			open++;
		else if (av[1][i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}

	solve(av[1], 0, open + close);
	return (0);
}
