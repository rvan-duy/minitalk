/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 17:11:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/31 17:50:14 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

pid_t client_pid;

static void	server_signal_handler(int sig, siginfo_t *info, void *context)
{
	g_signal = sig;
	client_pid = info->si_pid;
	(void)info;
	(void)context;
}

static void	listen_for_signals(void)
{
	char			buffer[SIZE_OF_BUFFER + 1];
	unsigned char	current_character;
	size_t			current_index;
	size_t			current_bit;

	current_character = 0;
	current_index = 0;
	current_bit = 1;
	ft_bzero(&buffer, SIZE_OF_BUFFER + 1);
	while (1)
	{
		sleep(SLEEPY_TIME_SECONDS);
		// if signal is 1, add the bit to current_character
		if (g_signal == SIGNAL_BIT_1)
			current_character += current_bit;
		
		current_bit <<= 1;

		// if the bit that is send is the 8th
		if (current_bit > LAST_BIT)
		{
			
			buffer[current_index] = current_character;

			if (current_character == '\0' || current_index == SIZE_OF_BUFFER)
			{
				ft_putstr_fd(buffer, STDOUT_FILENO);
				if (current_character == '\0')
					ft_putchar_fd('\n', STDOUT_FILENO);
				ft_bzero(&buffer, SIZE_OF_BUFFER + 1);
				current_index = 0;
			}
			else
				current_index += 1;
			
			current_character = 0;
			current_bit = 1;
			
		}
		
		// dprintf(2, "[%s] {%zu} [%c]\n", buffer, current_buffer_size, current_character);
		g_signal = 0;
		kill(client_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	g_signal = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &server_signal_handler;
	sigaction(SIGNAL_BIT_1, &sa, NULL);
	sigaction(SIGNAL_BIT_0, &sa, NULL);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	listen_for_signals();
	return (EXIT_SUCCESS);
}
