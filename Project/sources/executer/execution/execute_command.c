/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:34:11 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 19:27:39 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	execute_local_bin(t_shell_data *data, t_command *cmd)
{
	int	r;
	int	exc_r;

	r = check_cmd_if_exist(data, cmd);
	if (r != 0)
		return (r);
	exc_r = execve(cmd->cmd_name, cmd->arguments, data->env__);
	if (exc_r == -1)
		return (errmsg_cmd("execve", NULL,
				strerror(errno), errno));
	return (1);
}

static int	execute_system_bin(t_shell_data *data, t_command *cmd)
{
	if (!cmd->cmd_name || cmd->cmd_name[0] == '\0')
		return (RET_NOT_FOUND_VALUE);
	if (check_cmd_isdir(cmd->cmd_name))
		return (RET_NOT_FOUND_VALUE);
	cmd->cmd_path = get_cmd_path(data, cmd->cmd_name);
	if (!cmd->cmd_path)
		return (RET_NOT_FOUND_VALUE);
	if (execve(cmd->cmd_path, cmd->arguments, data->env__) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (1);
}

int	execute_builtin_command(t_shell_data *data, t_command *cmd)
{
	int	r;

	r = RET_NOT_FOUND_VALUE;
	if (ft_strncmp(cmd->cmd_name, "pwd", 4) == 0)
		r = pwd_builtin_cmd(data, cmd->arguments);
	else if (ft_strncmp(cmd->cmd_name, "echo", 5) == 0)
		r = echo_builtin_cmd(cmd->arguments);
	else if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		r = env_builtin_cmd(data, cmd->arguments);
	else if (ft_strncmp(cmd->cmd_name, "cd", 3) == 0)
		r = cd_builtin_cmd(data, cmd->arguments);
	else if (ft_strncmp(cmd->cmd_name, "export", 7) == 0)
		r = export_builtin_cmd(data, cmd->arguments);
	else if (ft_strncmp(cmd->cmd_name, "unset", 6) == 0)
		r = unset_builtin_cmd(data, cmd->arguments);
	else if (ft_strncmp(cmd->cmd_name, "exit", 5) == 0)
		r = exit_builtin_cmd(data, cmd->arguments);
	return (r);
}

static int	handle_cmd_execution(t_shell_data *data, t_command *cmd)
{
	int	r;

	r = execute_builtin_command(data, cmd);
	if (r != RET_NOT_FOUND_VALUE)
		return (r);
	r = execute_system_bin(data, cmd);
	if (r != RET_NOT_FOUND_VALUE)
		return (r);
	return (execute_local_bin(data, cmd));
}

int	shell_execute_command(t_shell_data *data, t_command *cmd)
{
	if (!validate_cmd_and_files(data, cmd))
		return (1);
	if (!set_pipe(data->cmd, cmd))
		return (1);
	if (!apply_redirection(cmd->_io_redirect))
	{
		reset_redirection(cmd->_io_redirect);
		return (1);
	}
	close_fds(data->cmd, false);
	if (!ft_strchr(cmd->cmd_name, '/'))
		return (handle_cmd_execution(data, cmd));
	return (execute_local_bin(data, cmd));
}
