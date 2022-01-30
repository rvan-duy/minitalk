/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:57:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/30 16:04:14 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

void	buffer_print(t_server_data *head)
{
	while (head != NULL)
	{
		ft_putstr_fd(head->buffer, STDOUT_FILENO);
		head = head->next;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

// clears all malloc'd buffers
// resets i and bit for head to 0 and 1
void	buffer_clear(t_server_data *head)
{
	t_server_data	*tmp;
	t_server_data	*tmp_2;

	ft_bzero(head->buffer, SIZE_OF_BUFFER);
	tmp_2 = head;
	if (head->next != NULL)
	{
		head = head->next;
		while (head != NULL)
		{
			tmp = head->next;
			free(head);
			head = tmp;
		}
	}
	ft_bzero(tmp_2, sizeof(t_server_data));
	tmp_2->current_bit = 1;
	tmp_2->current_index = 0;
}

void	buffer_increase(t_server_data *head)
{
	t_server_data	*new_node;

	new_node = malloc(sizeof(t_server_data));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->next = NULL;
	new_node->current_bit = 1;
	new_node->current_index = 0;
	while (head->next != NULL)
		head = head->next;
	head->next = new_node;
}

void	buffer_increment_values(t_server_data *head)
{
	if (head->current_index == 1000)
		head = head->next;
	
	
}
