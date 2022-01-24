#include "minitalk_bonus.h"

void	send_bit(int pid, uint8_t bit)
{
	if (bit == 0)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

void	send_char(t_send *send, int pid, char c, int wait)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		send_bit(pid, c & (1 << bit));
		bit++;
		if (wait == TRUE)
		{
			wait_for_confirm();
			send->confirm_bit_received = 0;
		}
	}
}

void	send_message(t_send send, int wait)
{
	while (*send.str)
	{
		send_char(&send, send.pid, *send.str, wait);
		send.str++;
		if (*send.str)
			send_bit(send.pid, 0);
	}
	send_bit(send.pid, 1);
}
