/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:06:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/26 14:17:39 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
		usleep(200);
		bit++;
		if (wait == TRUE)
		{
			if (wait_and_execute(CONFIRM, &g_talk, receive_bit_confirm))
			{
				ft_putstr_fd("\nError while sending message. Please try again.\n\n", 1);
				exit (EXIT_FAILURE);
			}
		}
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
			{
				if (wait_and_execute(CONFIRM, &g_talk, receive_bit_confirm))
				{
					ft_putstr_fd("\nError while sending message. Please try again.\n\n", 1);
					exit (EXIT_FAILURE);
				}
			}
			else
				usleep(200);
		}
	}
	kill(server_pid, END_OF_MESSAGE);
	usleep(200);
}

static void	send_pid(int pid)
{
	char	*str;
	int		server_pid;

	server_pid = pid;
	str = ft_itoa(getpid());
	if (!str)
	{
		ft_putendl_fd("Error at send_pid().", 2);
		exit(EXIT_FAILURE);
	}
	send_message(str, server_pid, FALSE);
	free(str);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client [pid] [Message]", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	g_talk.server_pid = ft_atoi(argv[1]);
	g_talk.str = argv[2];
	send_pid(g_talk.server_pid);
	send_message(g_talk.str, g_talk.server_pid, TRUE);
	ft_putendl_fd("Message sent.", 1);
	return (EXIT_SUCCESS);
}
