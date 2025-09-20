/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 01:30:22 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/22 18:52:38 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	open_heredoc_write_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

static void	child_heredoc_handler(t_shell_data *data, t_redirect *io, int fd)
{
	bool	success;
	int		delims_left;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	delims_left = 1;
	success = fill_heredoc(data, io, fd, &delims_left);
	close(fd);
	if (success)
		_exit(0);
	_exit(1);
}

int	handle_heredoc_result(t_redirect *io, int status, char *file_name)
{
	if (WIFSIGNALED(status))
	{
		get_status_exit_in_sig(130);
		free(file_name);
		return (300);
	}
	if (io->fd_in >= 0)
		close(io->fd_in);
	io->fd_in = open(file_name, O_RDONLY);
	if (io->fd_in < 0)
	{
		free(file_name);
		return (404);
	}
	unlink(file_name);
	free(file_name);
	return (200);
}

int	execute_heredoc(t_shell_data *data, t_redirect *io)
{
	pid_t			pid;
	int				fd;
	int				status;
	char			*file_name;
	struct termios	original;

	file_name = ft_strdup(io->in_file_name);
	if (!file_name)
		return (404);
	tcgetattr(STDIN_FILENO, &original);
	fd = open_heredoc_write_fd(file_name);
	if (fd < 0)
		return (free(file_name), 404);
	pid = fork();
	if (pid < 0)
		return (close(fd), free(file_name), 404);
	if (pid == 0)
		child_heredoc_handler(data, io, fd);
	close(fd);
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &original);
	return (handle_heredoc_result(io, status, file_name));
}

bool	handle_heredoc(t_shell_data *data, t_token **token, t_command **cmd)
{
	t_command	*last;
	t_redirect	*io;
	t_token		*tmp;
	int			result;

	if (!token || !*token || !(*token)->next || !cmd || !*cmd)
		return (false);
	tmp = *token;
	last = get_last_command(*cmd);
	if (!last)
		return (false);
	init_redir_struct(last);
	io = last->_io_redirect;
	if (!io)
		return (false);
	io->break_delimiter = get_delimiter(
			tmp->next->token_content, &io->has_quotes);
	io->in_file_name = get_heredoc_name();
	if (!io->break_delimiter || !io->in_file_name)
		return (false);
	result = execute_heredoc(data, io);
	return (heredoc_res(io, result));
}
