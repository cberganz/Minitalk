#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/include/libft.h"
# include <signal.h>
# include <stdint.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define BIT_0 SIGUSR1
# define BIT_1 SIGUSR2
# define CONFIRM SIGUSR2
# define GO_TO_NEXT_CHAR SIGUSR1
# define END_OF_MESSAGE SIGUSR2

typedef struct	s_talk
{
	int			sig;
	int			server_pid;
	int			client_pid;
	uint8_t		confirm;
	char		c;
	char		*str;
}	t_talk;

void			ft_join_free(t_talk *talk);
void			show_pid(void);
int8_t			wait_and_execute(int sig, t_talk *talk, void (*ft)(int));

#endif
