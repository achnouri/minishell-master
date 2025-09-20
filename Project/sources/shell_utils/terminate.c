/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:57:33 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/19 00:38:28 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_io_redirect_fds(t_redirect *io, bool close_backup)
{
	if (io->fd_in != -1)
	{
		close(io->fd_in);
		io->fd_in = -1;
	}
	if (io->fd_out != -1)
	{
		close(io->fd_out);
		io->fd_out = -1;
	}
	if (close_backup)
		reset_redirection(io);
}

static void	close_pipe_fds(int *pipe_fds)
{
	if (pipe_fds[0] != -1)
		close(pipe_fds[0]);
	if (pipe_fds[1] != -1)
		close(pipe_fds[1]);
	free(pipe_fds);
}

void	close_fds(t_command *commands, bool close_backup)
{
	t_command	*cmd;

	cmd = commands;
	while (cmd)
	{
		if (cmd->_io_redirect)
			close_io_redirect_fds(cmd->_io_redirect, close_backup);
		if (cmd->pipe_fds)
		{
			close_pipe_fds(cmd->pipe_fds);
			cmd->pipe_fds = NULL;
		}
		cmd = cmd->next;
	}
}

void	terminate_shell(t_shell_data *data, int exit_code)
{
	if (data)
	{
		if (data->cmd && data->cmd->_io_redirect)
			close_fds(data->cmd, true);
		free_shell_data(data, true);
	}
	if (exit_code != 42)
		exit(exit_code);
}

int	ft_word_count(char *str, char sep)
{
	int		i;
	int		count;
	bool	in_word;

	i = 0;
	count = 0;
	in_word = false;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != sep && !in_word)
		{
			in_word = true;
			count++;
		}
		else if (str[i] == sep)
			in_word = false;
		i++;
	}
	return (count);
}
