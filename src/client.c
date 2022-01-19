/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 12:59:02 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/19 17:51:51 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	char_to_signal(unsigned char character, pid_t pid)
{
	int	i;
	int	bit;

	i = 0;
	printf("sending %c to server...\n", character);
	while (i < 8)
	{
		bit = 1 & character;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		character = character >> 1;
		i++;
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	const int		server_pid = ft_atoi(argv[1]);
	const char		*string_to_send = ft_strdup(argv[2]);
	const size_t	string_len = ft_strlen(string_to_send);
	size_t			i;

	i = 0;
	if (string_to_send == NULL)
		return (EXIT_FAILURE);
	if (argc == 3)
	{
		while (i < string_len)
		{
			char_to_signal(string_to_send[i], server_pid);
			i++;
		}
		// kill(server_pid, SIGSTOP);
		// ft_putnbr_fd(server_pid, STDOUT_FILENO);
		// ft_putchar_fd('\n', STDOUT_FILENO);
		// ft_putendl_fd(string_to_send, STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
