#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int	match_space(FILE *f)
{
	int	c;

	c = fgetc(f);
	while (isspace(c))
		c = fgetc(f);
	if (c != EOF)
		ungetc(c, f);
	return (0);
}

int	match_char(FILE *f, char c)
{
	int	r;

	r = fgetc(f);
	if (r == c)
		return (1);
	if (r != EOF)
		ungetc(r, f);
	return (-1);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*c;
	int		r;

	c = va_arg(ap, char *);
	r = fgetc(f);
	if (r == EOF)
		return (-1);
	*c = r;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int		*n;
	int		c;
	int		sign;
	int		nb;

	n = va_arg(ap, int *);
	c = fgetc(f);
	sign = 1;
	nb = 0;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	if (!isdigit(c))
	{
		if (c != EOF)
			ungetc(c, f);
		return (-1);
	}
	while (isdigit(c))
	{
		nb = nb * 10 + (c - '0');
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	*n = nb * sign;
	return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	char	*s;
	int		c;
	int		i;

	s = va_arg(ap, char *);
	i = 0;
	c = fgetc(f);
	if (c == EOF)
		return (-1);
	while (c != EOF && !isspace(c))
	{
		s[i++] = c;
		c = fgetc(f);
	}
	s[i] = '\0';
	if (c != EOF)
		ungetc(c, f);
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return (scan_char(f, ap));
		case 'd':
			match_space(f);
			return (scan_int(f, ap));
		case 's':
			match_space(f);
			return (scan_string(f, ap));
		case EOF:
			return (-1);
		default:
			return (-1);
	}
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	nconv;
	int	c;

	nconv = 0;
	c = fgetc(f);
	if (c == EOF)
		return (EOF);
	ungetc(c, f);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return (EOF);
	return (nconv);
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
