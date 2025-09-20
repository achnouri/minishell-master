/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:36:06 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/23 23:15:46 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	close_pipe(t_command *commands, t_command *ignore_cmd)
{
	while (commands)
	{
		if (commands != ignore_cmd && commands->pipe_fds)
		{
			if (commands->pipe_fds[0] != -1)
				close(commands->pipe_fds[0]);
			if (commands->pipe_fds[1] != -1)
				close(commands->pipe_fds[1]);
			free(commands->pipe_fds);
			commands->pipe_fds = NULL;
		}
		commands = commands->next;
	}
}

bool	set_pipe(t_command *cmds, t_command *cmd)
{
	static int	pipe_count = 0;

	if (!cmd)
		return (false);
	if (cmd->has_pipe)
	{
		pipe_count++;
		if (pipe_count > MAX_PIPES_ALLOWED)
		{
			errno = EAGAIN;
			perror("minishell: fork");
			return (false);
		}
	}
	if (cmd->previous && cmd->previous->has_pipe && cmd->previous->pipe_fds)
		dup2(cmd->previous->pipe_fds[0], STDIN_FILENO);
	if (cmd->has_pipe && cmd->pipe_fds)
		dup2(cmd->pipe_fds[1], STDOUT_FILENO);
	close_pipe(cmds, cmd);
	return (true);
}

static bool	free_old_pipe(t_command *cmd)
{
	if (!cmd->pipe_fds)
		return (true);
	if (cmd->pipe_fds[0] != -1)
		close(cmd->pipe_fds[0]);
	if (cmd->pipe_fds[1] != -1)
		close(cmd->pipe_fds[1]);
	free(cmd->pipe_fds);
	cmd->pipe_fds = NULL;
	return (true);
}

static bool	init_new_pipe(t_shell_data *data, t_command *cmd)
{
	int	*fd;

	fd = ft_malloc(sizeof(int) * 2);
	if (!fd || pipe(fd) != 0)
	{
		perror("pipe");
		if (fd)
			free(fd);
		free_shell_data(data, false);
		return (false);
	}
	cmd->pipe_fds = fd;
	return (true);
}

bool	create_pipe(t_shell_data *data)
{
	t_command	*curr_cmd;

	curr_cmd = data->cmd;
	while (curr_cmd)
	{
		if (curr_cmd->has_pipe
			|| (curr_cmd->previous && curr_cmd->previous->has_pipe))
		{
			free_old_pipe(curr_cmd);
			if (!init_new_pipe(data, curr_cmd))
				return (false);
		}
		curr_cmd = curr_cmd->next;
	}
	return (true);
}
