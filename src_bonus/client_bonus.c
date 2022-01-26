#include "minitalk_bonus.h"

t_talk	talk;

static void	receive_bit_confirm(int sig)
{
	talk.confirm = 1;
	(void)sig;
}

static void	send_char(t_talk *talk, int pid, char c, int wait)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) == 0)
			kill(pid, BIT_0);
		else
			kill(pid, BIT_1);
		usleep(50);
		bit++;
		if (wait == TRUE)
			wait_and_execute(CONFIRM, talk, receive_bit_confirm);
	}
}

static void	send_message(t_talk *talk, int wait)
{
	int	i;

	i = 0;
	while (talk->str[i])
	{
		send_char(talk, talk->server_pid, talk->str[i], wait);
		i++;
		if (talk->str[i])
		{
			kill(talk->server_pid, GO_TO_NEXT_CHAR);
			if (wait == TRUE)
				wait_and_execute(CONFIRM, talk, receive_bit_confirm);
			else
				usleep(50);
		}
	}
	kill(talk->server_pid, END_OF_MESSAGE);
	usleep(50);
}

static void	send_pid(int pid)
{
	t_talk	send_pid;

	send_pid.server_pid = pid;
	send_pid.str = ft_itoa(getpid());
	if (!send_pid.str)
	{
		ft_putendl_fd("Error at send_pid().", 2);
		exit(EXIT_FAILURE);
	}
	send_message(&send_pid, FALSE);
	free(send_pid.str);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client [pid] [Message]", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	talk.server_pid = ft_atoi(argv[1]);
	talk.str = argv[2];
	send_pid(talk.server_pid);
	send_message(&talk, TRUE);
	ft_putendl_fd("Message sent.", 1);
	return (EXIT_SUCCESS);
}
