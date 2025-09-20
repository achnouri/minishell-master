/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:01:12 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 19:01:14 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	is_quiet_mode(t_shell_data *shell_data)
{
	t_command	*cmd;

	cmd = shell_data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->previous != NULL)
		return (true);
	return (false);
}

static void	handle_exit_no_args(t_shell_data *data)
{
	get_status_exit_in_sig(-1);
	terminate_shell(data, -42);
}

static int	handle_exit_with_args(t_shell_data *data, char **args)
{
	bool	error;
	int		exit_code;

	error = false;
	get_status_exit_in_sig(get_exit_code(args[1], &error,
			get_status_exit_in_sig(-1)));
	if (error)
	{
		exit_code = errmsg_cmd("exit", args[1], "numeric argument required", 2);
		terminate_shell(data, -42);
	}
	else if (args[2])
		return (errmsg_cmd("exit", NULL, "too many arguments", 1));
	exit_code = get_status_exit_in_sig(-1);
	terminate_shell(data, -42);
	return (0);
	return (exit_code);
}

int	exit_builtin_cmd(t_shell_data *data, char **args)
{
	bool	quiet;

	quiet = is_quiet_mode(data);
	if (!quiet)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		handle_exit_no_args(data);
	else
		return (handle_exit_with_args(data, args));
	return (0);
}
