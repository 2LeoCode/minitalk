#include <minitalk_client.h>

static volatile bool	g_sig_caught = false;

void	wait_signal(void)
{
	int	cnt;

	cnt = 0;
	while (!g_sig_caught)
	{
		usleep(1);
		if (++cnt == 1000)
		{
			ft_putstr("Failed to send message, aborting\n");
			exit(EXIT_FAILURE);
		}
	}
	g_sig_caught = false;
}

static void	sig_handler(int sig)
{
	g_sig_caught = true;
	(void)sig;
}

static void	send_null_byte(pid_t ppid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		kill(ppid, SIGUSR2);
		wait_signal();
	}	
}

static void	send_message_to_server(pid_t ppid, const unsigned char *msg)
{
	unsigned char	mask;

	print_info_msg(ppid, (const char *)msg);
	while (*msg)
	{
		mask = 1 << 7;
		while (mask)
		{
			if (*msg & mask)
				kill(ppid, SIGUSR1);
			else
				kill(ppid, SIGUSR2);
			wait_signal();
			mask >>= 1;
		}
		msg++;
	}
	send_null_byte(ppid);
	if (BONUS)
		ft_putstr("Message successfully sent\n");
}

int	main(int argc, char **argv)
{
	int					ppid;
	struct sigaction	act;

	if (argc != 3)
	{
		write(2, "Invalid arguments\n", 18);
		return (1);
	}
	ppid = ft_atoi(argv[1]);
	if (ppid < 2)
	{
		write(2, "Invalid server PID\n", 19);
		return (1);
	}
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sig_handler;
	sigaction(SIGUSR1, &act, 0);
	send_message_to_server(ppid, (const unsigned char *)argv[2]);
	return (0);
}
