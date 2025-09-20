/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:28:24 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/22 11:09:06 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	check_infile_outfile(t_redirect *io)
{
	if (!io || (!io->in_file_name && !io->out_file_name))
		return (true);
	if ((io->in_file_name && io->fd_in == -1)
		|| (io->out_file_name && io->fd_out == -1))
		return (false);
	return (true);
}

bool	reset_redirection(t_redirect *io_redir)
{
	int	r;

	r = true;
	if (!io_redir)
		return (r);
	if (io_redir->fd_stdin_backup != -1)
	{
		if (dup2(io_redir->fd_stdin_backup, STDIN_FILENO) == -1)
			r = false;
		close(io_redir->fd_stdin_backup);
		io_redir->fd_stdin_backup = -1;
	}
	if (io_redir->fd_stdout_backup != -1)
	{
		if (dup2(io_redir->fd_stdout_backup, STDOUT_FILENO) == -1)
			r = false;
		close(io_redir->fd_stdout_backup);
		io_redir->fd_stdout_backup = -1;
	}
	return (r);
}

bool	apply_redirection(t_redirect *io_redir)
{
	int	r;

	r = true;
	if (!io_redir)
		return (r);
	io_redir->fd_stdin_backup = dup(STDIN_FILENO);
	if (io_redir->fd_stdin_backup == -1)
		r = errmsg_cmd("dup", "stdin_backup",
				strerror(errno), false);
	io_redir->fd_stdout_backup = dup(STDOUT_FILENO);
	if (io_redir->fd_stdout_backup == -1)
		r = errmsg_cmd("dup", "stdout_backup",
				strerror(errno), false);
	if (io_redir->fd_in != -1)
		if (dup2(io_redir->fd_in, STDIN_FILENO) == -1)
			r = errmsg_cmd("dup2", io_redir->in_file_name,
					strerror(errno), false);
	if (io_redir->fd_out != -1)
		if (dup2(io_redir->fd_out, STDOUT_FILENO) == -1)
			r = errmsg_cmd("dup2", io_redir->out_file_name,
					strerror(errno), false);
	return (r);
}
