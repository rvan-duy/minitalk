/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 15:56:26 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/19 18:02:55 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data {
	pid_t	server_pid;
	char	*string_to_send;
	size_t	string_to_send_len;
}	t_data;

#endif
