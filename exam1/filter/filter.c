#define _GNU_SOURCE

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int	error(void)
{
	perror("Error");
	return (1);
}

static int	print_stars(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (write(1, "*", 1) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	char	buf[1024];
	char	*keep;
	char	*tmp;
	char	*found;
	ssize_t	r;
	size_t	plen;
	size_t	klen;
	size_t	part;

	if (ac != 2 || !av[1][0])
		return (1);
	plen = strlen(av[1]);
	keep = calloc(1, 1);
	if (!keep)
		return (error());
	klen = 0;
	while ((r = read(0, buf, sizeof(buf))) > 0)
	{
		tmp = realloc(keep, klen + r + 1);
		if (!tmp)
		{
			free(keep);
			return (error());
		}
		keep = tmp;
		memmove(keep + klen, buf, r);
		klen += r;
		keep[klen] = '\0';
		part = 0;
		while ((found = memmem(keep + part, klen - part, av[1], plen)))
		{
			write(1, keep + part, found - (keep + part));
			if (print_stars(plen))
			{
				free(keep);
				return (1);
			}
			part = (found - keep) + plen;
		}
		if (part)
		{
			memmove(keep, keep + part, klen - part);
			klen -= part;
			keep[klen] = '\0';
		}
		if (klen > plen)
		{
			write(1, keep, klen - plen + 1);
			memmove(keep, keep + klen - plen + 1, plen - 1);
			klen = plen - 1;
			keep[klen] = '\0';
		}
	}
	if (r < 0)
	{
		free(keep);
		return (error());
	}
	if (klen)
		write(1, keep, klen);
	free(keep);
	return (0);
}
