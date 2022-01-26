/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 17:11:41 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/26 17:27:30 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdio.h>

static void	client_signal_handler(int sig, siginfo_t *info, void *context)
{
	sig = g_signal;
	(void)info;
	(void)context;
}

// SIGUSR1 = 1
// SIGUSR2 = 0
static t_return_status	send_bit_to_pid(t_client_data *data)
{
	const char		current_character = data->string_to_send[data->current_index];
	const size_t	bit_to_send = data->current_bit & current_character;
	int				ret;

	if (bit_to_send != 0)
		ret = kill(data->server_pid, SIGUSR1);
	else
		ret = kill(data->server_pid, SIGUSR2);
	if (ret == -1)
		return (FAILED_SENDING_SIGNAL);
	data->current_bit = data->current_bit << 1;
	if (data->current_bit > 128)
	{
		data->current_bit = 1;
		data->current_index = data->current_index + 1;
	}
	return (FINISHED_SUCCESFULLY);
}

// sends signal to server
// - send bit to server using sending function..?
// waits
// if correct send another one.. until ya know
static void	send_starting_signal(t_client_data *data)
{
	const size_t	strlen = ft_strlen(data->string_to_send);

	g_signal = 0;
	send_bit_to_pid(data);
	while (1)
	{
		if (g_signal == MY_SIGNAL_STOP | data->current_index >= strlen)
			return ;
		else if (g_signal == MY_SIGNAL_CONT)
			send_bit_to_pid(data);
		// pause
	}
}

// opvangen van ret signals van server
int	main(int argc, char **argv)
{
	t_client_data		data;
	struct sigaction	sa;

	if (argc == 3)
	{
		client_parse(&data, argv);
		ft_bzero(&sa, sizeof(struct sigaction));
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &client_signal_handler;
		sigaction(MY_SIGNAL_CONT, &sa, NULL);
		sigaction(MY_SIGNAL_STOP, &sa, NULL);
		send_starting_signal(&data);
	}
	return (EXIT_SUCCESS);
}
