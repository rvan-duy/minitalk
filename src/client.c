/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 12:59:02 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/14 16:31:14 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	char_to_signal(unsigned char character, pid_t pid)
{
	const size_t	len = sizeof(character) * 8;
	size_t			i;

	i = 8;
	while (i > 0)
	{
		if (character & (1 << i))
			printf("1");
		else
			printf("0");
		i++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	const int	server_pid = ft_atoi(argv[1]);
	const char	*string_to_send = ft_strdup(argv[2]);

	if (string_to_send == NULL)
		return (EXIT_FAILURE);
	if (argc == 3)
	{
		kill(server_pid, SIGSTOP);
		ft_putnbr_fd(server_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putendl_fd(string_to_send, STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
