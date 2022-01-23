/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 12:59:02 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/23 14:35:54 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	char_to_signal(unsigned char character, pid_t pid)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = 1 & character;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		character = character >> 1;
		i++;
		usleep(50);
	}
}

static t_data	*parse_arguments(char **arguments)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		exit(EXIT_FAILURE);
	data->server_pid = ft_atoi(arguments[1]);
	data->string_to_send = ft_strdup(arguments[2]);
	if (data->string_to_send == NULL)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	data->string_to_send_len = ft_strlen(data->string_to_send);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	size_t	i;

	if (argc != 3)
		return (EXIT_FAILURE);
	data = parse_arguments(argv);
	char_to_signal(data->string_to_send_len, data->server_pid);
	i = 0;
	while (data->string_to_send[i])
	{
		char_to_signal(data->string_to_send[i], data->server_pid);
		i++;
	}
	free(data->string_to_send);
	free(data);
	return (EXIT_SUCCESS);
}
