#ifndef MINITALK_SERVER_H
# define MINITALK_SERVER_H

# include <signal.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>

# define DEFAULT_CAPACITY 32

typedef struct  s_string
{
    size_t  len;
    size_t  capacity;
    char    data[];
}   t_string;

size_t	ft_strlen(const char *s);
int		ft_putchar(int c);
int		ft_putstr(const char *s);
int		ft_putnbr(int nb);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		init_string(t_string **addr);
void	ft_abort(void);
int	    ft_strappend(t_string **s_ptr, char c);


#endif
