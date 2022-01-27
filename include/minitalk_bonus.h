/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:39:20 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/27 20:38:59 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

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

typedef struct s_talk
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
void			wait_and_execute(int sig, t_talk *talk, void (*ft)(int));
uint8_t			pid_is_not_natural(char *s);

#endif
