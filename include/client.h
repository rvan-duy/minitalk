/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:57:46 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/26 16:47:42 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "structs.h"
# include "libft.h"
# include <stdlib.h>

int	g_signal;

void	client_parse(t_client_data *data, char **arguments);

#endif
