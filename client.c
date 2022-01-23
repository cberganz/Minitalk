#include "minitalk.h"

int	main(int argc, char *argv[])
{
	t_send	send;

	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client [pid] [Message]", STDERR_FILENO);
		return (1);
	}
	send.pid = ft_atoi(argv[1]);
	send.str = argv[2];
	send_message(send);
	return (0);
}
