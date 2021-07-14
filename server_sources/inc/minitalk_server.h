#ifndef MINITALK_SERVER_H
# define MINITALK_SERVER_H

# include <signal.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>

# ifndef BONUS
#  define BONUS 0
# endif

# define DEFAULT_CAPACITY 32

typedef struct s_string
{
	size_t	len;
	size_t	capacity;
	char	data[];
}	t_string;

# if BONUS == 1

extern struct s_thread_infos
{
	pthread_t		thread;
	volatile bool	active;
} g_loading_thread;

# endif

size_t	ft_strlen(const char *s);
int		ft_putchar(int c);
int		ft_putstr(const char *s);
int		ft_putnbr(int nb);
void	*ft_mempcpy(void *dst, const void *src, size_t bytes);
void	ft_bzero(void *m, size_t bytes);
int		init_string(t_string **addr);
void	ft_abort(void);
int		ft_strappend(t_string **s_ptr, char c);
void	display_and_free_message(t_string *msg);

#endif
