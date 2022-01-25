#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/include/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

typedef struct	s_send
{
	int			pid;
	uint8_t		confirm_str_received;
	uint8_t		confirm_bit_received;
	char		*str;
}	t_send;

typedef struct	s_receive
{
	int			sig;
	uint8_t		pid_received;
	uint8_t		msg_received;
	char		c;
	char		*str;
	char		*client_pid;
}	t_receive;

void			send_bit(int pid, uint8_t bit);
void			send_char(t_send *send, int pid, char c, int wait);
void			send_message(t_send *send, int wait);
uint8_t			read_bit(int sig);
uint8_t			receive_char(t_receive *r);
void			receive_str(int sig);
void			ft_join_free(t_receive *r);
void			show_pid(void);
void			wait_for_confirm(void);

#endif
