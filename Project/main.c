/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:17:51 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/24 00:33:26 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_status_exit_in_sig(int val)
{
	static int	status;

	if (val == RET_LAST_EXIT_NUM)
		return (status);
	if (val != -1)
		status = val;
	return (status);
}

static bool	parsing_line_input(t_shell_data *data)
{
	int	flag_check;

	flag_check = init_check_line_input(data);
	if (flag_check == 0)
		return (false);
	else if (flag_check == 1)
		return (true);
	add_history(data->line_input);
	if (tokens(data, data->line_input) == FAILURE)
		return (false);
	if (data->token->token_type == END)
		return (false);
	if (check_env_and_syntax_errors(&data->token) == FAILURE)
	{
		get_status_exit_in_sig(258);
		return (false);
	}
	expand_env_vars(data, &data->token);
	process_tokens_remove_quotes(data);
	if (!creat_commands(data, data->token))
		return (false);
	return (true);
}

void	signal_reset_shell(int sig)
{
	if (sig == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		get_status_exit_in_sig(1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	start_minishell(t_shell_data *data)
{
	bool	parsing_success;

	rl_catch_signals = 0;
	signal(SIGINT, signal_reset_shell);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data->line_input = readline(GREEN "minishell$ " RESET);
		parsing_success = parsing_line_input(data);
		if (parsing_success)
			get_status_exit_in_sig(shell_execution(data));
		free_shell_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell_data	data;

	ft_memset(&data, 0, sizeof(t_shell_data));
	if (!init_data(&data, env) || !check_first_arg(ac, av))
		terminate_shell(NULL, EXIT_FAILURE);
	start_minishell(&data);
	return (0);
}
