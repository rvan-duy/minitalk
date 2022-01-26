/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 15:56:26 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/25 14:55:31 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <signal.h>
# include <stdbool.h>

typedef struct s_data {
	pid_t			server_pid;
	char			*string_to_send;
	size_t			string_to_send_len;
}	t_data;

typedef struct s_signal_variables {
	size_t			current_bit;
	unsigned char	current_char;
	bool			string_allocated;
	size_t			string_len;
	size_t			i;
}	t_signal_variables;

#endif
