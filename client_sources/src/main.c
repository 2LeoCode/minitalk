#include <minitalk_client.h>

void	send_message_to_server(pid_t ppid, const unsigned char *msg)
{
	unsigned char	mask;
	int				i;

	ft_putstr("Sending message `");
	ft_putstr((const char *)msg);
	ft_putstr("` to server_sources: ");
	ft_putnbr(ppid);
	ft_putchar('\n');
	while (*msg)
	{
		mask = 1 << 7;
		while (mask)
		{
			if (*msg & mask)
				kill(ppid, SIGUSR1);
			else
				kill(ppid, SIGUSR2);
			usleep(100);
			mask >>= 1;
		}
		msg++;
	}
	i = -1;
	while (++i < 8)
	{
		kill(ppid, SIGUSR2);
		usleep(100);
	}
	ft_putstr("Message successfully sent\n");
}

int	main(int argc, char **argv)
{
	int					ppid;

	if (argc != 3)
	{
		write(2, "Invalid arguments\n", 18);
		return (1);
	}
	ppid = ft_atoi(argv[1]);
	send_message_to_server(ppid, (const unsigned char *)argv[2]);
	return (0);
}
