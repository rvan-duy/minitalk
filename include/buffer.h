/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:59:20 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/30 16:50:09 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include "structs.h"
# include "libft.h"

void	buffer_print(char *buffer);
char	*buffer_clear(char *buffer, size_t *current_buffer_size);
char	*buffer_resize(char *buffer, size_t *current_buffer_size);

#endif
