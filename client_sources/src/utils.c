#include <minitalk_client.h>

int	ft_atoi(const char *s)
{
	int	n;
	int	ng;

	n = 0;
	ng = 1;
	if (*s == '-' || *s == '+')
		ng -= 2 * (*s++ == '-');
	while (*s >= '0' && *s <= '9')
		n = n * 10 + *s++ - 48;
	return (n * ng);
}

size_t	ft_strlen(const char *s)
{
	const char	*beg = s;

	while (*s)
		s++;
	return ((size_t)s - (size_t)beg);
}

int	ft_putchar(int c)
{
	const char	ch = c;

	return (write(1, &ch, 1));
}

int	ft_putstr(const char *s)
{
	return (write(1, s, ft_strlen(s)));
}

int	ft_putnbr(int nb)
{
	unsigned int	u;
	int				ret;

	ret = 0;
	u = (unsigned int)nb;
	if (nb < 0)
	{
		ret = write(1, "-", 1);
		u = -(long)nb;
	}
	if (u < 10)
		return (ret + ft_putchar(u + 48));
	ret += ft_putnbr(u / 10);
	ret += ft_putnbr(u % 10);
	return (ret);
}
