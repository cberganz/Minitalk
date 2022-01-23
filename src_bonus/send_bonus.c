#include "minitalk_bonus.h"

void	send_bit(int pid, uint8_t bit)
{
	if (bit == 0)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		send_bit(pid, c & (1 << bit));
		bit++;
	}
}

void	send_message(t_send send)
{
	while (*send.str)
	{
		send_char(send.pid, *send.str);
		if (*(send.str + 1))
			send_bit(send.pid, 0);
		send.str++;
	}
	send_bit(send.pid, 1);
}
