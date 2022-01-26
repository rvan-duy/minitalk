/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 17:11:39 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/26 17:42:34 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_signal_handler(int sig, siginfo_t *info, void *context)
{
	sig = g_signal;
	(void)info;
	(void)context;
}

static void	listen_for_signals(void)
{
	static t_server_data	data;

	ft_bzero(&data, sizeof(t_server_data));
	data.current_bit = 1;
	data.current_index = 0;
	while (1)
	{
		if (g_signal == SIGNAL_BIT_1)
			data.buffer[data.current_index] += data.current_bit;
		data.current_bit *= 2;
		if (data.current_bit > 128)
		{
			data.current_bit = 1;
		}
		pause();
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &server_signal_handler;
	sigaction(SIGNAL_BIT_1, &sa, NULL);
	sigaction(SIGNAL_BIT_0, &sa, NULL);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	listen_for_signals();
	return (EXIT_SUCCESS);
}
