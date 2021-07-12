#include <minitalk_server.h>

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
	ret += ft_putnbr(nb / 10);
	ret += ft_putnbr(nb % 10);
	return (ret);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*src_s = (const char *)src;
	char		*dst_s;

	dst_s = (char *)dst;
	while (n--)
		*dst_s++ = *src_s++;
	return (dst);
}
