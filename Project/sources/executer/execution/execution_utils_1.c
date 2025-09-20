/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:25:48 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/24 01:36:54 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	validate_cmd_and_files(t_shell_data *data, t_command *cmd)
{
	(void)data;
	if (!cmd || !cmd->cmd_name)
	{
		errmsg_cmd("child process", NULL,
			"no command to execute", 1);
		return (false);
	}
	if (!check_infile_outfile(cmd->_io_redirect))
		return (false);
	return (true);
}

void	close_previous_pipe(t_command *cmd)
{
	if (cmd->previous && cmd->previous->pipe_fds)
	{
		close(cmd->previous->pipe_fds[0]);
		close(cmd->previous->pipe_fds[1]);
		free(cmd->previous->pipe_fds);
		cmd->previous->pipe_fds = NULL;
	}
}
