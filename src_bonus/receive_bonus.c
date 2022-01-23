#include "minitalk_bonus.h"
	
uint8_t	receive_bit(int sig)
{
	if (sig == SIGUSR1)
		return (0);
	else
		return (1);
}

uint8_t receive_char(t_receive *r)
{
	static int	bit;
	
	if (bit < 8 && receive_bit(r->sig) == 1)
		r->c |= 1 << bit;	
	bit++;
	if (bit == 9)
	{
		bit = 0;
		if (receive_bit(r->sig) == 1)
			return (2);
		return (1);
	}
	return (0);
}
