/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:57:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/31 15:39:21 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include <stdio.h>

void	buffer_print(char *buffer)
{
	ft_putstr_fd(buffer, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	buffer_reset(char **buffer, size_t *current_buffer_size, size_t *current_index)
{
	free(*buffer);
	*current_buffer_size = SIZE_OF_BUFFER;
	*current_index = 0;
	*buffer = ft_calloc(SIZE_OF_BUFFER + 1, sizeof(char));
	if (*buffer == NULL)
		exit(EXIT_FAILURE);
	(*buffer)[SIZE_OF_BUFFER] = '\0';
}

char 	*buffer_resize(char *buffer, size_t *current_buffer_size)
{
	char *new_buffer;
	const size_t	new_buffer_size = *current_buffer_size * 2;	
	
	new_buffer = ft_calloc(new_buffer_size + 1, sizeof(char));
	if (new_buffer == NULL)
		exit(EXIT_FAILURE);
	new_buffer[new_buffer_size] = '\0';
	ft_memcpy(new_buffer, buffer, *current_buffer_size);
	// dprintf(2, "current_buffer_size: %zu\n", *current_buffer_size);
	free(buffer);
	// buffer 1000 current_buffer_size
	// new buffer 2000 current_buffer_size *2
	*current_buffer_size = new_buffer_size;
	return(new_buffer);
}

// void	buffer_resize(char **buffer, size_t *current_buffer_size)
// {
// 	const size_t	new_buffer_size = *current_buffer_size * 2;
// 	char			*old_buffer;

// 	dprintf(2, "Resizing buffer?\n");
// 	old_buffer = *buffer;
// 	*buffer = malloc(sizeof(char) * new_buffer_size + 1);
// 	if (*buffer == NULL)
// 		exit(EXIT_FAILURE);
// 	(*buffer)[new_buffer_size] = '\0';
// 	ft_memcpy(buffer, old_buffer, *current_buffer_size);
// 	free(old_buffer);
// 	*current_buffer_size = new_buffer_size;
// }
