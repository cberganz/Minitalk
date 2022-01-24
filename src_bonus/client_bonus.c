#include "minitalk_bonus.h"

t_send	send;

void	send_pid(int pid)
{
	t_send	send_pid;

	send_pid.pid = pid;
	send_pid.str = ft_itoa(getpid());
	if (!send_pid.str)
	{
		ft_putendl_fd("Error at send_pid().", 2);
		exit(EXIT_FAILURE);
	}
	send_message(send_pid, FALSE);
	free(send_pid.str);
}

void	receive_str_confirm(int sig)
{
	if (sig == SIGUSR2)
		ft_putendl_fd("Message received by server.", 1);
	else if (sig == SIGUSR1)
		ft_putendl_fd("Server did not receive message.", 1);
	send.confirm_str_received = 1;
}

void	receive_bit_confirm(int sig)
{
	send.confirm_bit_received = 1;
	(void)sig;
}

void	wait_for_confirm(void)
{
	signal(SIGUSR1, receive_str_confirm);
	signal(SIGUSR2, receive_bit_confirm);
	while (send.confirm_str_received == 0 || send.confirm_bit_received == 0)
		pause();
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client [pid] [Message]", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	send.pid = ft_atoi(argv[1]);
	send.str = argv[2];
	send_pid(send.pid);
	send_message(send, TRUE);
	ft_putendl_fd("Message sent.", 1);
	wait_for_confirm();
	return (EXIT_SUCCESS);
}
