/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:06:59 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/27 20:38:49 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	wait_and_execute(int sig, t_talk *talk, void (*ft)(int))
{
	if (sig == BIT_0 || sig == BIT_0 + BIT_1)
		signal(BIT_0, ft);
	if (sig == BIT_1 || sig == BIT_0 + BIT_1)
		signal(BIT_1, ft);
	while (talk->confirm == 0)
		pause();
	if (talk->confirm == 1)
		talk->confirm = 0;
}

void	show_pid(void)
{
	char	*pid_to_str;

	pid_to_str = ft_itoa(getpid());
	if (!pid_to_str)
	{
		ft_putendl_fd("Error at show_pid().", 2);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("Pid : ", 1);
	ft_putendl_fd(pid_to_str, 1);
	ft_putendl_fd("", 1);
	free(pid_to_str);
}

void	ft_join_free(t_talk *talk)
{
	char	*tmp;

	if (talk->str)
	{
		tmp = talk->str;
		talk->str = ft_strjoin(talk->str, &talk->c);
		free(tmp);
	}
	else
		talk->str = ft_strdup(&talk->c);
	if (!talk->str)
	{
		ft_putendl_fd("Error at receive_str().", 2);
		exit(EXIT_FAILURE);
	}
}

uint8_t	pid_is_not_natural(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (1);
		s++;
	}
	return (0);
}
