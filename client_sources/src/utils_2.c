#include <minitalk_client.h>

void	print_info_msg(pid_t ppid, const char *msg)
{
	ft_putstr("Sending message `");
	ft_putstr(msg);
	ft_putstr("` to server: ");
	ft_putnbr(ppid);
	ft_putchar('\n');
}
