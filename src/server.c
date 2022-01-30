/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 17:11:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/30 17:29:43 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

pid_t g_client_pid;

// OK SO TWO IDEAS FOR NEXT TIME:
// 1. JUST WRITE THE CHARACTERS, DONT BOTHER WITH THE BUFFER AT ALL
// 2. 

static void	server_signal_handler(int sig, siginfo_t *info, void *context)
{
	g_signal = sig;
	g_client_pid = info->si_pid;
	// usleep(1000);
	// if (info->si_errno == 0)
	// 	kill(info->si_pid, MY_SIGNAL_CONT);
	// else
	// 	kill(info->si_pid, MY_SIGNAL_STOP);
	(void)context;
}

static void	listen_for_signals(void)
{
	t_server_data	data;

	data.buffer = ft_calloc(SIZE_OF_BUFFER + 1, sizeof(char));
	data.current_bit = 1;
	data.current_index = 0;
	data.current_buffer_size = SIZE_OF_BUFFER;
	while (1)
	{
		pause();
		if (g_signal == SIGNAL_BIT_1)
		{
			if (data.current_index >= data.current_buffer_size)
			{
				// dprintf(2, "Resizing buffer: [%s] size: %zu\n", data.buffer, data.current_buffer_size);
				data.buffer = buffer_resize(data.buffer, &data.current_buffer_size);
			}
			data.buffer[data.current_index] += data.current_bit;
			// dprintf(2, "New buffer: [%s] size: %zu\n", data.buffer, data.current_buffer_size);
		}
		data.current_bit <<= 1;
		if (data.current_bit > 128)
		{
			if (data.buffer[data.current_index] == '\0')
			{
				buffer_print(data.buffer);
				dprintf(2, "Clearing buffer: [%s] size: %zu\n", data.buffer, data.current_buffer_size);
				data.buffer = buffer_clear(data.buffer, &data.current_buffer_size);
				dprintf(2, "New buffer: [%s] size: %zu\n", data.buffer, data.current_buffer_size);
				data.current_index = 0;
			}
			else
				data.current_index += 1;
			data.current_bit = 1;
		}
		usleep(200);
		kill(g_client_pid, MY_SIGNAL_CONT);
		g_signal = 0;
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
