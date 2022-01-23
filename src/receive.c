#include "minitalk.h"
	
uint8_t	receive_bit(int sig)
{
	if (sig == SIGUSR1)
		return (0);
	else
		return (1);
}

uint8_t receive_char(t_receive *r)
{
	if (r->bit < 8 && receive_bit(r->sig) == 1)
		r->c |= 1 << r->bit;	
	r->bit++;
	if (r->bit == 9)
	{
		r->bit = 0;
		if (receive_bit(r->sig) == 1)
			return (2);
		return (1);
	}
	return (0);
}

void	receive_str(int sig)
{
	static t_receive	r;
	uint8_t				ret;

	r.sig = sig;
	ret = receive_char(&r);
	if (ret >= 1)
	{
		ft_join_free(&r);
		r.c = 0;
	}
	if (ret == 2)
	{
		ft_putendl_fd(r.str, STDOUT_FILENO);
		free(r.str);
		r.str = NULL;
	}
}
