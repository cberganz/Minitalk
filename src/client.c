/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:06:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/27 20:39:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_talk	g_talk;

static void	receive_bit_confirm(int sig)
{
	g_talk.confirm = 1;
	(void)sig;
}

static void	send_char(int pid, char c, int wait)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) == 0)
			kill(pid, BIT_0);
		else
			kill(pid, BIT_1);
		if (wait == FALSE)
			usleep(2000);
		bit++;
		if (wait == TRUE)
			wait_and_execute(CONFIRM, &g_talk, receive_bit_confirm);
	}
}

static void	send_message(char *str, int server_pid, int wait)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(server_pid, str[i], wait);
		i++;
		if (str[i])
		{
			kill(server_pid, GO_TO_NEXT_CHAR);
			if (wait == TRUE)
				wait_and_execute(CONFIRM, &g_talk, receive_bit_confirm);
			else
				usleep(2000);
		}
	}
	usleep(200);
	kill(server_pid, END_OF_MESSAGE);
	usleep(200);
}

static void	send_pid(void)
{
	char	*str;

	str = ft_itoa(getpid());
	if (!str)
	{
		ft_putendl_fd("Error at send_pid().", 2);
		exit(EXIT_FAILURE);
	}
	send_message(str, g_talk.server_pid, FALSE);
	free(str);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client [pid] [Message]", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argv[2][0] == '\0')
	{
		ft_putendl_fd("Error.\nYour message is empty.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (pid_is_not_natural(argv[1]))
	{
		ft_putendl_fd("Error.\nPid is not natural.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	g_talk.server_pid = ft_atoi(argv[1]);
	g_talk.str = argv[2];
	usleep(500);
	send_pid();
	usleep(500);
	send_message(g_talk.str, g_talk.server_pid, TRUE);
	ft_putendl_fd("Message received by server.", 1);
	return (EXIT_SUCCESS);
}
