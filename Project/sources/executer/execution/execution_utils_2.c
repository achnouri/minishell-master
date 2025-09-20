/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:49:17 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/24 01:24:20 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	check_cmd_isdir(char *command)
{
	struct stat	info;

	if (stat(command, &info) != 0)
		return (false);
	return (S_ISDIR(info.st_mode));
}

int	check_cmd_if_exist(t_shell_data *data, t_command *cmd)
{
	if (ft_strchr(cmd->cmd_name, '/') == NULL
		&& get_env_var_index(data->env__, "PATH") != -1)
	{
		get_status_exit_in_sig(127);
		return (errmsg_cmd(cmd->cmd_name, NULL,
				"command not found", 127));
	}
	if (access(cmd->cmd_name, F_OK) != 0)
		return (errmsg_cmd(cmd->cmd_name, NULL,
				strerror(errno), RET_NOT_FOUND_VALUE));
	if (check_cmd_isdir(cmd->cmd_name))
		return (errmsg_cmd(cmd->cmd_name, NULL,
				"is a directory", 126));
	if (access(cmd->cmd_name, X_OK) != 0)
		return (errmsg_cmd(cmd->cmd_name, NULL,
				strerror(errno), RET_NOT_FOUND_VALUE));
	return (0);
}

int	initialize_execution(t_shell_data *data)
{
	if (!data || !data->cmd)
		return (0);
	if (!data->cmd->cmd_name)
	{
		if (data->cmd->_io_redirect)
		{
			if (!check_infile_outfile(data->cmd->_io_redirect))
				return (1);
			apply_redirection(data->cmd->_io_redirect);
			reset_redirection(data->cmd->_io_redirect);
		}
		return (1);
	}
	if (!create_pipe(data))
		return (1);
	return (RET_NOT_FOUND_VALUE);
}

bool	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	return (
		ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0
	);
}
