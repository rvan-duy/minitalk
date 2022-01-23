/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 14:02:19 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/23 15:06:29 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

static void	server_signal_handler(int sig)
{
	g_signal = sig;
}

static void	init_sigaction(struct sigaction *sa)
{
	g_signal = 0;
	sa->sa_flags = SA_RESTART;
	sa->sa_handler = &server_signal_handler;
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
}

static void	reset_signal_vars(t_signal_variables *signal_vars)
{
	signal_vars->current_bit = 1;
	signal_vars->current_char = 0;
	signal_vars->string_allocated = false;
	signal_vars->string_len = 0;
	signal_vars->i = 0;
}

static char	*allocate_string(t_signal_variables *signal_vars)
{
	char	*new_str;

	signal_vars->string_len = signal_vars->current_char;
	new_str = malloc(sizeof(char) * signal_vars->string_len);
	if (new_str == NULL)
		exit(EXIT_FAILURE);
	new_str[signal_vars->string_len] = '\0';
	signal_vars->string_allocated = true;
	return (new_str);
}

// split up in more functions, make this readable
static void	process_signal(void)
{
	static t_signal_variables	signal_vars = {1, 0, false, 0, 0};
	static char					*string_to_receive;

	if (g_signal == SIGUSR1)
		signal_vars.current_char += signal_vars.current_bit;
	signal_vars.current_bit *= 2;
	if (signal_vars.current_bit > 128)
	{
		if (signal_vars.string_allocated == false)
			string_to_receive = allocate_string(&signal_vars);
		else
			string_to_receive[signal_vars.i++] = signal_vars.current_char;
		signal_vars.current_bit = 1;
		signal_vars.current_char = 0;
	}
	if (signal_vars.i == signal_vars.string_len
		&& signal_vars.string_allocated == true)
	{
		ft_putendl_fd(string_to_receive, STDOUT_FILENO);
		free(string_to_receive);
		reset_signal_vars(&signal_vars);
	}
	g_signal = 0;
}

int	main(void)
{
	struct sigaction	sa;

	init_sigaction(&sa);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	while (true)
	{
		if (g_signal == SIGUSR1 || g_signal == SIGUSR2)
			process_signal();
	}
	return (EXIT_SUCCESS);
}
