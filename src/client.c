/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 17:11:41 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/30 17:28:28 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdio.h>

static void	client_signal_handler(int sig, siginfo_t *info, void *context)
{
	g_signal = sig;
	(void)info;
	(void)context;
}

static t_return_status	send_bit_to_pid(t_client_data *data)
{
	const char		current_character = data->string_to_send[data->current_index];
	const size_t	bit_to_send = data->current_bit & current_character;
	int				ret;

	if (bit_to_send != 0)
		ret = kill(data->server_pid, SIGNAL_BIT_1);
	else
		ret = kill(data->server_pid, SIGNAL_BIT_0);
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

// TODO: error handling
static void	send_starting_signal(t_client_data *data)
{
	const size_t	strlen = ft_strlen(data->string_to_send);

	g_signal = 0;
	send_bit_to_pid(data);
	while (1)
	{
		pause();
		if (g_signal == MY_SIGNAL_STOP || data->current_index > strlen)
			return ;
		else if (g_signal == MY_SIGNAL_CONT)
		{
			dprintf(2, "Sending over a bit..\n");
			usleep(1000);
			send_bit_to_pid(data);
		}
	}
}

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
