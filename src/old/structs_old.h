/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 11:51:36 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/30 15:29:36 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MY_SIGNAL_CONT SIGUSR1
# define MY_SIGNAL_STOP SIGUSR2
# define SIGNAL_BIT_1 SIGUSR1
# define SIGNAL_BIT_0 SIGUSR2
# define SIZE_OF_BUFFER 1000

# include <signal.h>

typedef struct s_server_data {
	char					buffer[SIZE_OF_BUFFER];
	size_t					current_index;
	size_t					current_bit;
	struct s_server_data	*next;
}	t_server_data;

typedef struct s_client_data {
	pid_t					server_pid;
	char					*string_to_send;
	size_t					current_index;
	size_t					current_bit;
}	t_client_data;

typedef enum s_return_status {
	FINISHED_SUCCESFULLY,
	FAILED_SENDING_SIGNAL
}	t_return_status;

#endif
