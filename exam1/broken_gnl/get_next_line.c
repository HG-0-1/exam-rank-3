#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = ft_strlen(*s1);
	tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	return (ft_memcpy(dest, src, n));
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*ret;
	char		*tmp;
	char		*after;
	size_t		remain;
	int			read_ret;

	ret = malloc(1);
	if (!ret)
		return (NULL);
	ret[0] = '\0';

	tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
		{
			free(ret);
			return (NULL);
		}

		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(ret);
			return (NULL);
		}

		b[read_ret] = '\0';

		if (read_ret == 0)
		{
			if (ret[0] == '\0')
			{
				free(ret);
				return (NULL);
			}
			return (ret);
		}

		tmp = ft_strchr(b, '\n');
	}

	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}

	after = tmp + 1;
	remain = ft_strlen(after);
	ft_memmove(b, after, remain + 1);

	return (ret);
}
int main()
{
    int fd = open("test.txt",O_RDONLY);
    char *line;
    while((line = get_next_line(fd)))
    {
     printf("%s",line);
     free(line);
    }
    close(fd);

}
