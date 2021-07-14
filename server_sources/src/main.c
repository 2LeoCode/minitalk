#include <minitalk_server.h>

void	display_and_free_message(t_string *msg)
{
	ft_putstr(msg->data);
	free(msg);
	ft_putchar('\n');
}

#if BONUS == 0

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	character;
	static t_string			*str;
	static bool				is_new_message = true;
	static unsigned char	mask = 1 << 7;

	(void)ucontext;
	if (is_new_message && init_string(&str))
		ft_abort();
	is_new_message = false;
	if (sig == SIGUSR1)
		character |= mask;
	mask >>= 1;
	if (!mask)
	{
		if (!character)
		{
			display_and_free_message(str);
			is_new_message = true;
		}
		else if (ft_strappend(&str, (char)character))
			ft_abort();
		character = 0;
		mask = 1 << 7;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;
	const pid_t			pid = getpid();

	sigemptyset(&act.sa_mask);
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	ft_putstr("Started minitalk server with pid: ");
	ft_putnbr(pid);
	ft_putchar('\n');
	while (1)
		pause();
	return (0);
}

#endif
