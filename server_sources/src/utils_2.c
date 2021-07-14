#include <minitalk_server.h>

int	init_string(t_string **addr)
{
	*addr = malloc(sizeof(t_string) + sizeof(char) * DEFAULT_CAPACITY);
	if (!*addr)
		return (-1);
	ft_bzero((*addr)->data, DEFAULT_CAPACITY);
	(*addr)->capacity = DEFAULT_CAPACITY;
	(*addr)->len = 0;
	return (0);
}

void	ft_abort(void)
{
	ft_putstr("Runtime error, aborting\n");
	exit(EXIT_FAILURE);
}

int	ft_strappend(t_string **s_ptr, char c)
{
	t_string	*new_s;

	if ((*s_ptr)->capacity == (*s_ptr)->len + 1)
	{
		(*s_ptr)->capacity *= 2;
		new_s = malloc(sizeof(t_string) + sizeof(char) * (*s_ptr)->capacity);
		new_s->capacity = (*s_ptr)->capacity;
		new_s->len = (*s_ptr)->len;
		if (new_s)
			ft_mempcpy(new_s->data, (*s_ptr)->data, (*s_ptr)->len);
		free(*s_ptr);
		if (!new_s)
			return (-1);
		ft_bzero(new_s->data + new_s->len, new_s->capacity - new_s->len);
		*s_ptr = new_s;
	}
	(*s_ptr)->data[(*s_ptr)->len++] = c;
	return (0);
}

void	*ft_mempcpy(void *dst, const void *src, size_t bytes)
{
	const uint64_t	*qword_src = (const uint64_t *)src;
	uint64_t		*qword_dst;
	size_t			padding;

	qword_dst = (uint64_t *)dst;
	while (bytes >= 8)
	{
		*qword_dst++ = *qword_src++;
		bytes -= 8;
	}
	dst = qword_dst;
	src = qword_src;
	if (bytes >= 4)
		*((uint32_t *)dst) = *((uint32_t *)src);
	padding = 4 * (bytes >= 4);
	if (bytes - padding >= 2)
		*((uint16_t *)(dst + padding)) = *((uint16_t *)(src + padding));
	padding += 2 * (bytes - padding >= 2);
	if (bytes - padding == 1)
		*((uint8_t *)dst + padding) = *((uint8_t *)src + padding);
	return (dst + padding);
}

void	ft_bzero(void *m, size_t bytes)
{
	uint64_t	*qword;
	size_t		padding;

	qword = (uint64_t *)m;
	while (bytes >= 8)
	{
		*qword++ = 0;
		bytes -= 8;
	}
	m = qword;
	if (bytes >= 4)
		*((uint32_t *)m) = 0;
	padding = 4 * (bytes >= 4);
	if (bytes - padding >= 2)
		*((uint16_t *)m + padding) = 0;
	padding += 2 * (bytes - padding >= 2);
	if (bytes - padding)
		*((uint8_t *)m + padding) = 0;
}
