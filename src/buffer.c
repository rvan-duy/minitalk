/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:57:50 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/30 17:18:13 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include <stdio.h>

void	buffer_print(char *buffer)
{
	ft_putstr_fd(buffer, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

char	*buffer_clear(char *buffer, size_t *current_buffer_size)
{
	char	*new_buffer;

	free(buffer);
	*current_buffer_size = SIZE_OF_BUFFER;
	new_buffer = ft_calloc(SIZE_OF_BUFFER + 1, sizeof(char));
	if (new_buffer == NULL)
		exit(EXIT_FAILURE);
	return (new_buffer);
}

// another idea is to just write stuff and clear buffer to re-use it
char	*buffer_resize(char *buffer, size_t *current_buffer_size)
{
	char	*new_buffer;

	*current_buffer_size += SIZE_OF_BUFFER;
	new_buffer = ft_realloc(buffer, *current_buffer_size + 1, sizeof(char));
	if (new_buffer == NULL)
		exit(EXIT_FAILURE);
	return (new_buffer);
}
