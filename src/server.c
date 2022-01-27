/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:06:52 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/27 19:42:58 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static t_talk	g_talk;

static uint8_t	receive_char(t_talk *talk)
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

	g_talk.sig = sig;
	ret = receive_char(&g_talk);
	if (ret >= 1)
	{
		ft_join_free(&g_talk);
		g_talk.c = 0;
	}
	if (ret == 2)
	{
		g_talk.client_pid = ft_atoi(g_talk.str);
		free(g_talk.str);
		g_talk.str = NULL;
		g_talk.confirm = 1;
	}
}

static void	receive_str(int sig)
{
	uint8_t				ret;

	g_talk.sig = sig;
	ret = receive_char(&g_talk);
	if (ret >= 1)
	{
		ft_join_free(&g_talk);
		g_talk.c = 0;
	}
	if (ret == 2)
	{
		ft_putendl_fd(g_talk.str, STDOUT_FILENO);
		g_talk.confirm = 1;
		free(g_talk.str);
		g_talk.str = NULL;
	}
	usleep(200);
	kill(g_talk.client_pid, CONFIRM);
}

int	main(void)
{
	show_pid();
	while (1)
	{
		wait_and_execute(BIT_0 + BIT_1, &g_talk, receive_id);
		ft_putstr_fd("From client ", STDOUT_FILENO);
		ft_putnbr_fd(g_talk.client_pid, STDOUT_FILENO);
		ft_putstr_fd(" : ", STDOUT_FILENO);
		wait_and_execute(BIT_0 + BIT_1, &g_talk, receive_str);
		ft_putendl_fd("", STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
