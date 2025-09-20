/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:17:27 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:17:27 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	handle_infile_removal(t_redirect *io)
{
	if (!io->in_file_name)
		return (true);
	if (io->fd_in == -1)
		return (false);
	if (io->break_delimiter)
	{
		safe_free(io->break_delimiter);
		io->break_delimiter = NULL;
		unlink(io->in_file_name);
	}
	safe_free(io->in_file_name);
	io->in_file_name = NULL;
	if (io->fd_in != -1 && io->fd_in != STDIN_FILENO)
	{
		close(io->fd_in);
		io->fd_in = -1;
	}
	return (true);
}

static bool	handle_outfile_removal(t_redirect *io)
{
	if (!io->out_file_name)
		return (true);
	if (io->fd_out == -1)
		return (false);
	safe_free(io->out_file_name);
	io->out_file_name = NULL;
	if (io->fd_out != -1 && io->fd_out != STDOUT_FILENO)
	{
		close(io->fd_out);
		io->fd_out = -1;
	}
	return (true);
}

bool	remove_old_file_ref(t_redirect *io, bool infile)
{
	if (!io)
		return (false);
	if (infile)
		return (handle_infile_removal(io));
	else
		return (handle_outfile_removal(io));
}

int	append_next_command_argument(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		len;
	char	**args_new;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	while (temp->token_type == ARG || temp->token_type == VAR)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (last_cmd->arguments[len])
		len++;
	args_new = ft_malloc(sizeof(char *) * (i + len + 1));
	if (!args_new)
		return (FAILURE);
	args_new = copy_tokens_into_args(len, args_new, last_cmd, token_node);
	free(last_cmd->arguments);
	last_cmd->arguments = args_new;
	*token_node = temp;
	return (SUCCESS);
}

int	creat_command_arguments(t_token **current_token, t_command *cmd)
{
	int		i;
	int		arg_count;
	t_token	*tmp;

	i = 0;
	tmp = *current_token;
	arg_count = count_simple_tokens(tmp);
	cmd->arguments = ft_malloc(sizeof(char *) * (arg_count + 2));
	if (!cmd->arguments)
		return (FAILURE);
	tmp = *current_token;
	cmd->arguments[i] = ft_strdup(cmd->cmd_name);
	i++;
	while (tmp->token_type == ARG || tmp->token_type == VAR)
	{
		cmd->arguments[i] = ft_strdup(tmp->token_content);
		i++;
		tmp = tmp->next;
	}
	cmd->arguments[i] = NULL;
	*current_token = tmp;
	return (SUCCESS);
}
