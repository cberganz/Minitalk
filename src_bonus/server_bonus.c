#include "minitalk_bonus.h"

static t_receive	r;

void	receive_id(int sig)
{
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
		r.client_pid = r.str;
		r.str = NULL;
		r.pid_received = 1;
	}
}

void	receive_str(int sig)
{
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
		r.msg_received = 1;
		free(r.str);
		r.str = NULL;
	}
}

void	receive_pid(void)
{
	signal(SIGUSR1, receive_id);
	signal(SIGUSR2, receive_id);
	while (r.pid_received == 0)
		pause();
}

void	receive_message(void)
{
	signal(SIGUSR1, receive_str);
	signal(SIGUSR2, receive_str);
	while (r.msg_received == 0)
		pause();
}

int	main(void)
{
	show_pid();
	while (1)
	{
		receive_pid();
		receive_message();
		r.pid_received = 0;
		r.msg_received = 0;
		usleep(500);
		send_bit(ft_atoi(r.client_pid), 1);
		free(r.client_pid);
		r.client_pid = NULL;
	}
	return (EXIT_SUCCESS);
}
