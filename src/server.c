#include "minitalk.h"

int	main(void)
{
	show_pid();
	signal(SIGUSR1, receive_str);
	signal(SIGUSR2, receive_str);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
