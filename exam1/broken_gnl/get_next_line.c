#include "get_next_line.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_strdup(char *s)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[j++] = s1[i++];
	}
	i = 0;
	while (s2 && s2[i])
	{
		new[j++] = s2[i++];
	}
	new[j] = '\0';
	free(s1);
	return (new);
}

static int	has_newline(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*extract_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new = malloc(ft_strlen(stash + i) + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (stash[i])
		new[j++] = stash[i++];
	new[j] = '\0';
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buf[BUFFER_SIZE + 1];
	int			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!has_newline(stash))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buf[r] = '\0';
		if (!stash)
			stash = ft_strdup("");
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (NULL);
	}
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	buf[0] = 0;
	buf[0] = 0;
	r = 0;
	(void)buf;
	(void)r;
	char *line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}














/////////\



////////////
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	pos;
	static int	bytes;
	char		*line;
	int			len;
	char		*tmp;

	line = NULL;
	len = 0;
	while (1)
	{
		if (pos >= bytes)
		{
			bytes = read(fd, buf, BUFFER_SIZE);
			pos = 0;
			if (bytes <= 0)
				break ;
		}
		tmp = malloc(len + 2);
		if (!tmp)
			return (free(line), NULL);
		for (int i = 0; i < len; i++)
			tmp[i] = line[i];
		tmp[len] = buf[pos++];
		tmp[len + 1] = '\0';
		free(line);
		line = tmp;
		len++;
		if (line[len - 1] == '\n')
			return (line);
	}
	if (len > 0)
		return (line);
	free(line);
	return (NULL);
}
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("h.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
