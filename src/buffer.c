/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:57:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/27 14:53:34 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

void	buffer_print(t_server_data *data)
{
	while (data != NULL)
	{
		ft_putstr_fd(data->buffer, STDOUT_FILENO);
		data = data->next;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

// clears all malloc'd buffers
// resets i and bit for head to 0 and 1
void	buffer_clear(t_server_data *data)
{
	t_server_data	*tmp;
	t_server_data	*tmp_2;

	ft_bzero(data->buffer, SIZE_OF_BUFFER);
	tmp_2 = data;
	if (data->next != NULL)
	{
		data = data->next;
		while (data != NULL)
		{
			tmp = data->next;
			free(data);
			data = tmp;
		}
	}
	ft_bzero(tmp_2, sizeof(t_server_data));
	tmp_2->current_bit = 1;
	tmp_2->current_index = 0;
}
