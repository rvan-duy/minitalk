/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 13:28:38 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/01/25 16:41:48 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	reset_signal_vars(t_signal_variables *signal_vars)
{
	signal_vars->current_bit = 1;
	signal_vars->current_char = 0;
	signal_vars->string_allocated = false;
	signal_vars->string_len = 0;
	signal_vars->i = 0;
}

// Allocates the string, uses current_char as len
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

static char	*process_byte(t_signal_variables *signal_vars, char *str_to_receive)
{
	if (signal_vars->string_allocated == false)
		return (allocate_string(signal_vars));
	else
	{
		str_to_receive[signal_vars->i] = signal_vars->current_char;
		signal_vars->i++;
		return (str_to_receive);
	}
}

static void	process_signal(int sig, siginfo_t *info)
{
	static t_signal_variables	signal_vars = {1, 0, false, 0, 0};
	static char					*string_to_receive;

	if (sig == SIGUSR1)
		signal_vars.current_char += signal_vars.current_bit;
	signal_vars.current_bit *= 2;
	if (signal_vars.current_bit > 128)
	{
		string_to_receive = process_byte(&signal_vars, string_to_receive);
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
	// ft_putendl_fd("sending signal back..", 2);
	kill(info->si_pid, SIGUSR1);
}

static void	server_signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGUSR1 || sig == SIGUSR2)
		process_signal(sig, info);
	else
	{
		ft_putendl_fd("Unknown signal received, exiting program.", 1);
		exit(EXIT_FAILURE);
	}
	(void)context;
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &server_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	// lars zegt pause is raar, bool volgens hem wel
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
