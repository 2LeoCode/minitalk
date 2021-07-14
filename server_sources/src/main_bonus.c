#include <minitalk_server.h>

#if BONUS == 1

struct s_thread_infos	g_loading_thread;

static void	display_string_and_disable_thread(t_string *str,
				bool *is_new_message)
{
	g_loading_thread.active = false;
	ft_putstr("\b\bOK\n");
	display_and_free_message(str);
	*is_new_message = true;
}

static void	init_string_and_enable_thread(t_string **s_ptr)
{
	if (init_string(s_ptr))
		ft_abort();
	ft_putstr("Receiving message from client\t--");
	g_loading_thread.active = true;
}

static void	*loading_loop(void *dummy)
{
	(void)dummy;
	while (42)
	{
		while (g_loading_thread.active)
		{
			sleep(1);
			if (g_loading_thread.active)
				ft_putstr("\b\b\\ ");
			sleep(1);
			if (g_loading_thread.active)
				ft_putstr("\b\b/ ");
			sleep(1);
			if (g_loading_thread.active)
				ft_putstr("\b\b--");
		}
		usleep(1);
	}
	return (NULL);
}

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	character;
	static t_string			*str;
	static bool				is_new_message = true;
	static unsigned char	mask = 1 << 7;

	(void)ucontext;
	if (is_new_message)
		init_string_and_enable_thread(&str);
	is_new_message = false;
	if (sig == SIGUSR1)
		character |= mask;
	mask >>= 1;
	if (!mask)
	{
		if (!character)
			display_string_and_disable_thread(str, &is_new_message);
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

	g_loading_thread.active = false;
	if (pthread_create(&g_loading_thread.thread, NULL, loading_loop, NULL))
		return (-1);
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
