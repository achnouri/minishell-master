/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:11:11 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/22 12:50:21 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_exit_status_from_child(int main_child_status)
{
	int	child_exit_status;

	if (WIFSIGNALED(main_child_status))
	{
		if (WTERMSIG(main_child_status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		child_exit_status = 128 + WTERMSIG(main_child_status);
	}
	else if (WIFEXITED(main_child_status))
		child_exit_status = WEXITSTATUS(main_child_status);
	else
		child_exit_status = main_child_status;
	return (child_exit_status);
}

static int	get_processes_children(t_shell_data *data)
{
	int		main_child_status;
	int		child_exit_status;
	pid_t	current_child_pid;

	close_fds(data->cmd, false);
	main_child_status = 0;
	current_child_pid = 0;
	while (current_child_pid != -1 || errno != ECHILD)
	{
		current_child_pid = waitpid(-1, &child_exit_status, 0);
		if (current_child_pid == -1 && errno == ECHILD)
			break ;
		if (WIFSIGNALED(child_exit_status)
			&& WTERMSIG(child_exit_status) == SIGQUIT)
			ft_putendl_fd("Quit: 3", 1);
		if (current_child_pid == data->pid)
			main_child_status = child_exit_status;
	}
	return (get_exit_status_from_child(main_child_status));
}

static int	handle_child_process(t_shell_data *data, t_command *cmd)
{
	int	r;

	signal(SIGQUIT, SIG_DFL);
	if (!set_pipe(data->cmd, cmd))
		exit(1);
	apply_redirection(cmd->_io_redirect);
	close_pipe(data->cmd, NULL);
	r = shell_execute_command(data, cmd);
	exit(r);
}

static int	create_processes_children(t_shell_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
		{
			close_fds(data->cmd, true);
			free_shell_data(data, false);
			perror("minishell: fork");
			return (1);
		}
		else if (data->pid == 0)
			handle_child_process(data, cmd);
		close_previous_pipe(cmd);
		cmd = cmd->next;
	}
	close_fds(data->cmd, false);
	return (get_processes_children(data));
}

int	shell_execution(t_shell_data *data)
{
	int	r;

	r = initialize_execution(data);
	get_status_exit_in_sig(r);
	if (r != RET_NOT_FOUND_VALUE)
		return (get_status_exit_in_sig(-1));
	if (data->cmd && !data->cmd->has_pipe && !data->cmd->previous
		&& !data->cmd->_io_redirect && is_builtin(data->cmd->cmd_name))
		return (execute_builtin_command(data, data->cmd));
	return (create_processes_children(data));
}
