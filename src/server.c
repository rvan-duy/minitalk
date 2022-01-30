/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 17:11:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/30 15:32:49 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>

static void	server_signal_handler(int sig, siginfo_t *info, void *context)
{
	g_signal = sig;
	usleep(50);
	if (info->si_errno == 0)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
	(void)context;
}

static void	listen_for_signals(void)
{
	t_server_data	*data;

	data = malloc(sizeof(t_server_data));
	data->next = NULL;
	data->current_bit = 1;
	data->current_index = 0;
	while (1)
	{
		// dprintf(2, "signal: %d\n", g_signal);
		pause();
		if (g_signal == SIGNAL_BIT_1)
			data->buffer[data->current_index] += data->current_bit;
		// dprintf(2, "%d\n", data->buffer[data->current_index]);
		data->current_bit <<= 1;
		// ft_putendl_fd(data->buffer, 2);
		if (data->current_bit > 128)
		{
			if (data->buffer[data->current_index] == '\0')
			{
				buffer_print(data);
				buffer_clear(data);
			}
			else
			{
				data->current_bit = 1;
				data->current_index += 1;
			}
		}
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
