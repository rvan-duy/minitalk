/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client_parse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 13:53:20 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/26 14:44:13 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_parse(t_client_data *data, char **arguments)
{
	data->server_pid = ft_atoi(arguments[1]);
	data->string_to_send = ft_strdup(arguments[2]);
	if (data->string_to_send == NULL)
		exit(EXIT_FAILURE);
	data->current_index = 0;
	data->current_bit = 1;
}
