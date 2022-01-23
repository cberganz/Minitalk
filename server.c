#include "minitalk.h"

static void	show_pid(void)
{
	char	*pid_to_str;

	pid_to_str = ft_itoa(getpid());
	if (!pid_to_str)
	{
		ft_putendl_fd("Error at show_pid()", 2);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("Pid : ", 1);
	ft_putendl_fd(pid_to_str, 1);
	free(pid_to_str);
}

int	main(void)
{
	show_pid();
	signal(SIGUSR1, receive_str);
	signal(SIGUSR2, receive_str);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
