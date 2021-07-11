#include <minitalk_server.h>

void	sig_handler(int sig)
{
	static unsigned char	character;
	static unsigned char	mask = 1 << 7;
	static bool				is_new_message = true;

	if (is_new_message)
	{
		ft_putstr("Received message from client_sources: ");
		is_new_message = false;
	}
	if (sig == SIGUSR1)
		character |= mask;
	mask >>= 1;
	if (!mask)
	{
		if (character)
			ft_putchar(character);
		else
		{
			ft_putchar('\n');
			is_new_message = true;
		}
		character = 0;
		mask = 1 << 7;
	}
}

int	main(void)
{
	struct sigaction	act;
	const pid_t			pid = getpid();

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_handler = sig_handler;

	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	ft_putstr("Started minitalk server_sources with pid: ");
	ft_putnbr(pid);
	ft_putchar('\n');
	while (1)
		pause();
	return (0);
}
