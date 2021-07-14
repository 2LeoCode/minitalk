#ifndef MINITALK_CLIENT_H
# define MINITALK_CLIENT_H

# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>

# ifndef BONUS
#  define BONUS 0
# endif

int		ft_atoi(const char *s);
size_t	ft_strlen(const char *s);
int		ft_putchar(int c);
int		ft_putstr(const char *s);
int		ft_putnbr(int nb);
void	print_info_msg(pid_t ppid, const char *msg);

#endif
