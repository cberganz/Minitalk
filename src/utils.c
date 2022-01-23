#include "minitalk.h"

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
	free(pid_to_str);
}

void	ft_join_free(t_receive *r)
{
	char	*tmp;

	if (r->str)
	{
		tmp = r->str;
		r->str = ft_strjoin(r->str, &r->c);
		free(tmp);
	}
	else
		r->str = ft_strdup(&r->c);
	if (!r->str)
	{
		ft_putendl_fd("Error at receive_str().", 2);
		exit(EXIT_FAILURE);
	}
}
