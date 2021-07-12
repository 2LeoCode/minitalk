#include <minitalk_server.h>

int		init_string(t_string **addr)
{
	*addr = malloc(sizeof(t_string) + sizeof(char) * DEFAULT_CAPACITY);
	if (!*addr)
		return (-1);
	*(*addr)->data = 0;
	(*addr)->capacity = DEFAULT_CAPACITY;
	(*addr)->len = 0;
	return (0);
}

void	ft_abort(void)
{
	ft_putstr("Allocation error, aborting\n");
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
			ft_memcpy(new_s->data, (*s_ptr)->data, (*s_ptr)->len);
		free(*s_ptr);
		if (!new_s)
			return (-1);
		*s_ptr = new_s;
	}
	(*s_ptr)->data[(*s_ptr)->len++] = c;
	(*s_ptr)->data[(*s_ptr)->len] = 0;
	return (0);
}
