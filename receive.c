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
//	char				*tmp;
//	size_t				len;
	static int			i;

	r.sig = sig;
	ret = receive_char(&r);
	if (ret >= 1)
	{
//		if (r.first_signal == 0)
//			len = 0;
//		else
//			len = ft_strlen(r.str);
//		tmp = malloc(sizeof(char) * (len + 2));
//		ft_strcpy(tmp, r.str);
//		tmp[len] = r.c;
//		tmp[len + 1] = '\0';
//		if (r.first_signal == 0)
//			r.first_signal = 1;
//		else
//			free(r.str);
//		r.str = tmp;
		if (i == 0)
		{
			r.str = malloc(999);
			ft_bzero(r.str, 999);
		}
		r.str[i] = r.c;
		i++;
		r.c = 0;
	}
	if (ret == 2)
	{
		ft_putstr_fd(r.str, STDOUT_FILENO);
		free(r.str);
		i = 0;
//		r.first_signal = 0;
	}
}
