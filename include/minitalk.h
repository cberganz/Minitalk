#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/include/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

typedef struct	s_send
{
	int			pid;
	char		*str;
}	t_send;

typedef struct	s_receive
{
	int			sig;
	uint8_t		bit;
	char		c;
	char		*str;
}	t_receive;

void			send_bit(int pid, uint8_t bit);
void			send_char(int pid, char c);
void			send_message(t_send send);
uint8_t			read_bit(int sig);
uint8_t			receive_char(t_receive *r);
void			receive_str(int sig);
void			ft_join_free(t_receive *r);
void			show_pid(void);

#endif
