/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 11:04:45 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/19 17:44:41 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	signal_handler(int sig)
{
	static size_t	current_bit = 1;
	static char		current_character = 0;

	printf("current_bit = %zu\n", current_bit);
	if (sig == 30)
	{
		printf("received sigusr1 signal: corresponding to bit 1\n");
		current_character += current_bit;
	}
	else if (sig == 31)
	{
		printf("received sigusr2 signal: corresponding to bit 0\n");
	}
	current_bit *= 2;
	if (current_bit > 128)
	{
		printf("found character: %c\n", current_character);
		current_bit = 1;
		current_character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		;
	return (0);
}
