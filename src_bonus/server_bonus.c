#include "minitalk_bonus.h"

static t_talk	talk;

static uint8_t receive_char(t_talk *talk)
{
	static int	bit;
	
	if (bit < 8 && talk->sig == BIT_1)
		talk->c |= 1 << bit;	
	bit++;
	if (bit == 9)
	{
		bit = 0;
		if (talk->sig == END_OF_MESSAGE)
			return (2);
		return (1);
	}
	return (0);
}

static void	receive_id(int sig)
{
	uint8_t				ret;

	talk.sig = sig;
	ret = receive_char(&talk);
	if (ret >= 1)
	{
		ft_join_free(&talk);
		talk.c = 0;
	}
	if (ret == 2)
	{
		talk.client_pid = ft_atoi(talk.str);
		free(talk.str);
		talk.str = NULL;
		talk.confirm = 1;
	}
}

static void	receive_str(int sig)
{
	uint8_t				ret;

	talk.sig = sig;
	ret = receive_char(&talk);
	if (ret >= 1)
	{
		ft_join_free(&talk);
		talk.c = 0;
	}
	if (ret == 2)
	{
		ft_putendl_fd(talk.str, STDOUT_FILENO);
		talk.confirm = 1;
		free(talk.str);
		talk.str = NULL;
	}
	usleep(100);
	kill(talk.client_pid, CONFIRM);
}

int	main(void)
{
	show_pid();
	while (1)
	{
		wait_and_execute(BIT_0 + BIT_1, &talk, receive_id);
		ft_putstr_fd("From client ", 1);
		ft_putnbr_fd(talk.client_pid, 1);
		ft_putstr_fd(" : ", 1);
		wait_and_execute(BIT_0 + BIT_1, &talk, receive_str);
	}
	return (EXIT_SUCCESS);
}
